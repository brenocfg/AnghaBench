#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  client_t ;
struct TYPE_8__ {scalar_t__ length; } ;
struct TYPE_7__ {int fd; scalar_t__ state; scalar_t__ read; scalar_t__ wrote; TYPE_3__ msg; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {int fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ MSG_READ ; 
 scalar_t__ MSG_WRITE ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__ client ; 
 int do_msg_read (int,TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int do_msg_write (int,TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ server ; 

void main_loop() {
  int res;
  fd_set fdr;
  fd_set fdw;

  // see if there are any connections to accept or read / write from
  FD_ZERO(&fdr);
  FD_ZERO(&fdw);
  FD_SET(server.fd, &fdr);
  FD_SET(server.fd, &fdw);
#if !TEST_DGRAM
  if (client.fd) FD_SET(client.fd, &fdr);
  if (client.fd) FD_SET(client.fd, &fdw);
#endif
  res = select(64, &fdr, &fdw, NULL, NULL);
  if (res == -1) {
    perror("select failed");
    exit(EXIT_SUCCESS);
  }

#if !TEST_DGRAM
  // for TCP sockets, we may need to accept a connection
  if (FD_ISSET(server.fd, &fdr)) {
#if TEST_ACCEPT_ADDR
    // Do an accept with non-NULL addr and addlen parameters. This tests a fix to a bug in the implementation of
    // accept which had a parameter "addrp" but used "addr" internally if addrp was set - giving a ReferenceError.
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    socklen_t addrlen = sizeof(addr);
    client.fd = accept(server.fd, (struct sockaddr *) &addr, &addrlen);
#else
    client.fd = accept(server.fd, NULL, NULL);
#endif
    assert(client.fd != -1);
  }
#endif

#if !TEST_DGRAM
    int fd = client.fd;
#else
    int fd = server.fd;
#endif
  if (client.state == MSG_READ) {

    if (!FD_ISSET(fd, &fdr)) {
      return;
    }

    socklen_t addrlen = sizeof(client.addr);
    res = do_msg_read(fd, &client.msg, client.read, 0, (struct sockaddr *)&client.addr, &addrlen);
    if (res == -1) {
      return;
    } else if (res == 0) {
      // client disconnected
      memset(&client, 0, sizeof(client_t));
      return;
    }

    client.read += res;

    // once we've read the entire message, echo it back
    if (client.read >= client.msg.length) {
      client.read = 0;
      client.state = MSG_WRITE;
    }
  }

  if (client.state == MSG_WRITE) {
    if (!FD_ISSET(fd, &fdw)) {
      return;
    }

    res = do_msg_write(fd, &client.msg, client.wrote, 0, (struct sockaddr *)&client.addr, sizeof(client.addr));
    if (res == -1) {
      return;
    } else if (res == 0) {
      // client disconnected
      memset(&client, 0, sizeof(client_t));
      return;
    }

    client.wrote += res;

    if (client.wrote >= client.msg.length) {
      client.wrote = 0;
      client.state = MSG_READ;

#if CLOSE_CLIENT_AFTER_ECHO
      close(client.fd);
      memset(&client, 0, sizeof(client_t));
#endif
    }
  }
}