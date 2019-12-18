#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dhk; } ;
struct TYPE_5__ {TYPE_1__ id_keys; } ;
struct TYPE_6__ {TYPE_2__ devcb; } ;
typedef  int /*<<< orphan*/  BT_OCTET16 ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  BT_OCTET16_LEN ; 
 TYPE_3__ btm_cb ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void BTM_GetDeviceDHK (BT_OCTET16 dhk)
{
    BTM_TRACE_DEBUG ("BTM_GetDeviceDHK");
    memcpy (dhk, btm_cb.devcb.id_keys.dhk, BT_OCTET16_LEN);
}