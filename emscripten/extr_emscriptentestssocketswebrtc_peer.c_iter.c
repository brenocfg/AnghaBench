#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* msg_iov; } ;
struct TYPE_4__ {scalar_t__ iov_base; } ;

/* Variables and functions */
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int done ; 
 int /*<<< orphan*/  emscripten_cancel_main_loop () ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 TYPE_2__ hdr ; 
 int /*<<< orphan*/  perror (char*) ; 
 int sendmsg (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock ; 
 int /*<<< orphan*/  stderr ; 

void iter() {
  int n;
  n = sendmsg(sock, &hdr, 0);

  if(0 < n) {
    done = 1;
    fprintf(stderr, "sent %d bytes: %s", n, (char*)hdr.msg_iov[0].iov_base);

    shutdown(sock, SHUT_RDWR);
    close(sock);

    exit(EXIT_SUCCESS);
    emscripten_cancel_main_loop();
  } else if(EWOULDBLOCK != errno) {
    perror("sendmsg failed");
    exit(EXIT_FAILURE);
    emscripten_cancel_main_loop();
  }
}