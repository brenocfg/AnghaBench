#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  buffers ;

/* Variables and functions */
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int send (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

void do_send(int sockfd) {
  static char* buffers[] = {
    "\x09\x01\x02\x03\x04\x05\x06\x07\x08\x09\0",
    "\x08\x01\x02\x03\x04\x05\x06\x07\x08\0",
    "\x07\x01\x02\x03\x04\x05\x06\x07\0",
    "\x06\x01\x02\x03\x04\x05\x06\0",
    "\x05\x01\x02\x03\x04\x05\0",
    "\x04\x01\x02\x03\x04\0",
    "\x03\x01\x02\x03\0",
    "\x02\x01\x02\0",
    "\x01\x01\0"
  };

  int i;
  int res;
  char *buffer;
  socklen_t addrlen;

  for (i = 0; i < sizeof(buffers) / sizeof(char*); i++) {
    buffer = buffers[i];

    res = send(sockfd, buffer, strlen(buffer), 0);
    if (res == -1) {
      perror("send failed");
      return;
    }
    printf("sent \"%s\" (%d bytes)\n", buffer, res);
  }
}