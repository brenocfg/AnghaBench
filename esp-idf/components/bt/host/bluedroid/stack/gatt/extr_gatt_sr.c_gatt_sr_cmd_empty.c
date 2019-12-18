#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ op_code; } ;
struct TYPE_5__ {TYPE_1__ sr_cmd; } ;
typedef  TYPE_2__ tGATT_TCB ;
typedef  int BOOLEAN ;

/* Variables and functions */

BOOLEAN gatt_sr_cmd_empty (tGATT_TCB *p_tcb)
{
    return (p_tcb->sr_cmd.op_code == 0);
}