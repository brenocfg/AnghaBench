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
 scalar_t__ MON_IDT ; 
 int /*<<< orphan*/  mips_desc ; 
 int /*<<< orphan*/  mips_error (char*) ; 
 int /*<<< orphan*/  mips_expect (char*) ; 
 scalar_t__ mips_monitor ; 
 scalar_t__ mips_receive_packet (char*,int,int) ; 
 scalar_t__ mips_receive_seq ; 
 int /*<<< orphan*/  mips_send_command (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ mips_send_seq ; 
 int /*<<< orphan*/  serial_write (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sleep (int) ; 

__attribute__((used)) static void
mips_enter_debug (void)
{
  /* Reset the sequence numbers, ready for the new debug sequence: */
  mips_send_seq = 0;
  mips_receive_seq = 0;

  if (mips_monitor != MON_IDT)
    mips_send_command ("debug\r", 0);
  else				/* assume IDT monitor by default */
    mips_send_command ("db tty0\r", 0);

  sleep (1);
  serial_write (mips_desc, "\r", sizeof "\r" - 1);

  /* We don't need to absorb any spurious characters here, since the
     mips_receive_header will eat up a reasonable number of characters
     whilst looking for the SYN, however this avoids the "garbage"
     being displayed to the user. */
  if (mips_monitor != MON_IDT)
    mips_expect ("\r");

  {
    char buff[DATA_MAXLEN + 1];
    if (mips_receive_packet (buff, 1, 3) < 0)
      mips_error ("Failed to initialize (didn't receive packet).");
  }
}