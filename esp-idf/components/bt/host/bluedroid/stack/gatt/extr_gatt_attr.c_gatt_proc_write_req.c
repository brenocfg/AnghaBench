#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/  value; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ tGATT_WRITE_REQ ;
typedef  int /*<<< orphan*/  tGATT_STATUS ;
typedef  int /*<<< orphan*/  tGATTS_REQ_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  GATTS_SetAttributeValue (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ GATT_MAX_ATTR_LEN ; 

tGATT_STATUS gatt_proc_write_req( tGATTS_REQ_TYPE type, tGATT_WRITE_REQ *p_data)
{
    if(p_data->len > GATT_MAX_ATTR_LEN) {
        p_data->len = GATT_MAX_ATTR_LEN;
    }
   return GATTS_SetAttributeValue(p_data->handle,
                           p_data->len,
                           p_data->value);

}