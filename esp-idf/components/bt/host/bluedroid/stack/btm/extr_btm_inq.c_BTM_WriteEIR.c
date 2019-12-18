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
typedef  int /*<<< orphan*/  tBTM_STATUS ;
struct TYPE_2__ {scalar_t__ (* supports_extended_inquiry_response ) () ;} ;
typedef  int /*<<< orphan*/  BT_HDR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_MODE_UNSUPPORTED ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_TRACE_API (char*) ; 
 int /*<<< orphan*/  btsnd_hcic_write_ext_inquiry_response (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* controller_get_interface () ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 () ; 

tBTM_STATUS BTM_WriteEIR( BT_HDR *p_buff, BOOLEAN fec_required)
{
    if (controller_get_interface()->supports_extended_inquiry_response()) {
        BTM_TRACE_API("Write Extended Inquiry Response to controller\n");
        btsnd_hcic_write_ext_inquiry_response (p_buff, fec_required);
        return BTM_SUCCESS;
    } else {
        osi_free(p_buff);
        return BTM_MODE_UNSUPPORTED;
    }
}