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
typedef  void* UINT8 ;
struct TYPE_2__ {void* err_status; void* req_op_code; int /*<<< orphan*/  enable_err_rsp; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*,int /*<<< orphan*/ ,void*,void*) ; 
 TYPE_1__ gatt_cb ; 

void gatt_set_err_rsp(BOOLEAN enable, UINT8 req_op_code, UINT8 err_status)
{
    GATT_TRACE_DEBUG("gatt_set_err_rsp enable=%d op_code=%d, err_status=%d", enable, req_op_code, err_status);
    gatt_cb.enable_err_rsp  = enable;
    gatt_cb.req_op_code     = req_op_code;
    gatt_cb.err_status      = err_status;
}