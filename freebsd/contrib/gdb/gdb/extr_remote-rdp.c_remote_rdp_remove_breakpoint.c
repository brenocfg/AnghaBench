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
 int /*<<< orphan*/  RDP_CLEAR_BREAK ; 
 TYPE_1__ ds ; 
 int /*<<< orphan*/  send_rdp (char*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
remote_rdp_remove_breakpoint (CORE_ADDR addr, char *save)
{
  int res;
  if (ds.rdi_level > 0)
    {
      send_rdp ("b-p-S-B",
		RDP_CLEAR_BREAK,
		save, 4,
		&res);
    }
  else
    {
      send_rdp ("bw-S-B",
		RDP_CLEAR_BREAK,
		addr,
		&res);
    }
  return res;
}