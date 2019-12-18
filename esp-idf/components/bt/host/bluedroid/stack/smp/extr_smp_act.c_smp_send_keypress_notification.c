#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tSMP_INT_DATA ;
struct TYPE_4__ {int /*<<< orphan*/  local_keypress_notification; } ;
typedef  TYPE_1__ tSMP_CB ;
typedef  int /*<<< orphan*/  UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  SMP_OPCODE_PAIR_KEYPR_NOTIF ; 
 int /*<<< orphan*/  smp_send_cmd (int /*<<< orphan*/ ,TYPE_1__*) ; 

void smp_send_keypress_notification(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    p_cb->local_keypress_notification = *(UINT8 *) p_data;
    smp_send_cmd(SMP_OPCODE_PAIR_KEYPR_NOTIF, p_cb);
}