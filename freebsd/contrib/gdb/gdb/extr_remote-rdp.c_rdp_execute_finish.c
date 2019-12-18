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
struct TYPE_2__ {int /*<<< orphan*/  rdi_stopped_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUIT ; 
#define  RDP_RESET 130 
#define  RDP_RES_SWI 129 
#define  RDP_RES_VALUE 128 
 int SERIAL_TIMEOUT ; 
 TYPE_1__ ds ; 
 int /*<<< orphan*/  handle_swi () ; 
 int /*<<< orphan*/  io ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  send_rdp (char*,int /*<<< orphan*/ *) ; 
 int serial_readchar (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rdp_execute_finish (void)
{
  int running = 1;

  while (running)
    {
      int res;
      res = serial_readchar (io, 1);
      while (res == SERIAL_TIMEOUT)
	{
	  QUIT;
	  printf_filtered ("Waiting for target..\n");
	  res = serial_readchar (io, 1);
	}

      switch (res)
	{
	case RDP_RES_SWI:
	  handle_swi ();
	  break;
	case RDP_RES_VALUE:
	  send_rdp ("B", &ds.rdi_stopped_status);
	  running = 0;
	  break;
	case RDP_RESET:
	  printf_filtered ("Target reset\n");
	  running = 0;
	  break;
	default:
	  printf_filtered ("Ignoring %x\n", res);
	  break;
	}
    }
}