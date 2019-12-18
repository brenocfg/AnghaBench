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
 int /*<<< orphan*/  DATA_MAXLEN ; 
 int mips_receive_packet (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_receive_wait ; 
 int /*<<< orphan*/  mips_send_packet (char*,int) ; 
 int /*<<< orphan*/  printf_filtered (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static void
pmon_command (char *args, int from_tty)
{
  char buf[DATA_MAXLEN + 1];
  int rlen;

  sprintf (buf, "0x0 %s", args);
  mips_send_packet (buf, 1);
  printf_filtered ("Send packet: %s\n", buf);

  rlen = mips_receive_packet (buf, 1, mips_receive_wait);
  buf[rlen] = '\0';
  printf_filtered ("Received packet: %s\n", buf);
}