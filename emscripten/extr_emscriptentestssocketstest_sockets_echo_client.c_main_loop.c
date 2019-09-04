#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_7__ {scalar_t__ length; int /*<<< orphan*/  buffer; } ;
struct TYPE_6__ {scalar_t__ length; } ;
struct TYPE_5__ {scalar_t__ state; int /*<<< orphan*/  fd; TYPE_4__ msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  FD_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FIONREAD ; 
 int /*<<< orphan*/  MESSAGE ; 
 scalar_t__ MSG_READ ; 
 scalar_t__ MSG_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 int do_msg_read (int /*<<< orphan*/ ,TYPE_4__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int do_msg_write (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__ echo_msg ; 
 scalar_t__ echo_read ; 
 scalar_t__ echo_wrote ; 
 int /*<<< orphan*/  finish (int /*<<< orphan*/ ) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void main_loop() {
  static char out[1024*2];
  static int pos = 0;
  fd_set fdr;
  fd_set fdw;
  int res;

  // make sure that server.fd is ready to read / write
  FD_ZERO(&fdr);
  FD_ZERO(&fdw);
  FD_SET(server.fd, &fdr);
  FD_SET(server.fd, &fdw);
  res = select(64, &fdr, &fdw, NULL, NULL);
  if (res == -1) {
    perror("select failed");
    finish(EXIT_FAILURE);
  }

  if (server.state == MSG_READ) {
    if (!FD_ISSET(server.fd, &fdr)) {
      return;
    }

#if !TEST_DGRAM
    // as a test, confirm with ioctl that we have data available
    // after selecting
    int available;
    res = ioctl(server.fd, FIONREAD, &available);
    assert(res != -1);
    assert(available);
#endif

    res = do_msg_read(server.fd, &server.msg, echo_read, 0, NULL, NULL);
    if (res == -1) {
      return;
    } else if (res == 0) {
      perror("server closed");
      finish(EXIT_FAILURE);
    }

    echo_read += res;

    // once we've read the entire message, validate it
    if (echo_read >= server.msg.length) {
      assert(!strcmp(server.msg.buffer, MESSAGE));
      finish(EXIT_SUCCESS);
    }
  }

  if (server.state == MSG_WRITE) {
    if (!FD_ISSET(server.fd, &fdw)) {
      return;
    }

    res = do_msg_write(server.fd, &echo_msg, echo_wrote, 0, NULL, 0);
    if (res == -1) {
      return;
    } else if (res == 0) {
      perror("server closed");
      finish(EXIT_FAILURE);
    }

    echo_wrote += res;

    // once we're done writing the message, read it back
    if (echo_wrote >= echo_msg.length) {
      server.state = MSG_READ;
    }
  }
}