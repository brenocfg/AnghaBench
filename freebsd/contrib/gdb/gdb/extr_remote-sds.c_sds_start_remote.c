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

/* Variables and functions */
 int /*<<< orphan*/  immediate_quit ; 
 int next_msg_id ; 
 int /*<<< orphan*/  printf_unfiltered (char*,...) ; 
 int readchar (int) ; 
 int /*<<< orphan*/  sds_desc ; 
 int /*<<< orphan*/  sds_send (unsigned char*,int) ; 
 int /*<<< orphan*/  serial_write (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  start_remote () ; 

__attribute__((used)) static int
sds_start_remote (void *dummy)
{
  int c;
  unsigned char buf[200];

  immediate_quit++;		/* Allow user to interrupt it */

  /* Ack any packet which the remote side has already sent.  */
  serial_write (sds_desc, "{#*\r\n", 5);
  serial_write (sds_desc, "{#}\r\n", 5);

  while ((c = readchar (1)) >= 0)
    printf_unfiltered ("%c", c);
  printf_unfiltered ("\n");

  next_msg_id = 251;

  buf[0] = 26;
  sds_send (buf, 1);

  buf[0] = 0;
  sds_send (buf, 1);

  immediate_quit--;

  start_remote ();		/* Initialize gdb process mechanisms */
  return 1;
}