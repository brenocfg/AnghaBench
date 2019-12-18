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
struct TYPE_2__ {scalar_t__ rdi_level; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  RDP_SET_BREAK ; 
 int RDP_SET_BREAK_TYPE_GET_HANDLE ; 
 int RDP_SET_BREAK_TYPE_PC_EQUAL ; 
 TYPE_1__ ds ; 
 int /*<<< orphan*/  send_rdp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 

__attribute__((used)) static int
remote_rdp_insert_breakpoint (CORE_ADDR addr, char *save)
{
  int res;
  if (ds.rdi_level > 0)
    {
      send_rdp ("bwb-SWB",
		RDP_SET_BREAK,
		addr,
		RDP_SET_BREAK_TYPE_PC_EQUAL | RDP_SET_BREAK_TYPE_GET_HANDLE,
		save,
		&res);
    }
  else
    {
      send_rdp ("bwb-SB",
		RDP_SET_BREAK,
		addr,
		RDP_SET_BREAK_TYPE_PC_EQUAL,
		&res);
    }
  return res;
}