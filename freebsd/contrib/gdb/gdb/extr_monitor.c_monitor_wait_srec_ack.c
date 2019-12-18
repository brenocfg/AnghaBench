#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int MO_SREC_ACK_PLUS ; 
 int MO_SREC_ACK_ROTATE ; 
 TYPE_1__* current_monitor ; 
 char readchar (int) ; 
 int timeout ; 

__attribute__((used)) static int
monitor_wait_srec_ack (void)
{
  int ch;

  if (current_monitor->flags & MO_SREC_ACK_PLUS)
    {
      return (readchar (timeout) == '+');
    }
  else if (current_monitor->flags & MO_SREC_ACK_ROTATE)
    {
      /* Eat two backspaces, a "rotating" char (|/-\), and a space.  */
      if ((ch = readchar (1)) < 0)
	return 0;
      if ((ch = readchar (1)) < 0)
	return 0;
      if ((ch = readchar (1)) < 0)
	return 0;
      if ((ch = readchar (1)) < 0)
	return 0;
    }
  return 1;
}