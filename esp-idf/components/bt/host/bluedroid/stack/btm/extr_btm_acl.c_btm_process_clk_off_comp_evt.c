#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_4__ {TYPE_1__* acl_db; } ;
struct TYPE_3__ {int /*<<< orphan*/  clock_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 size_t MAX_L2CAP_LINKS ; 
 TYPE_2__ btm_cb ; 
 size_t btm_handle_to_acl_index (int /*<<< orphan*/ ) ; 

void btm_process_clk_off_comp_evt (UINT16 hci_handle, UINT16 clock_offset)
{
    UINT8      xx;
    BTM_TRACE_DEBUG ("btm_process_clk_off_comp_evt\n");
    /* Look up the connection by handle and set the current mode */
    if ((xx = btm_handle_to_acl_index(hci_handle)) < MAX_L2CAP_LINKS) {
        btm_cb.acl_db[xx].clock_offset = clock_offset;
    }
}