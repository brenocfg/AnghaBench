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
typedef  int /*<<< orphan*/  tBTM_LINK_KEY_CALLBACK ;
struct TYPE_3__ {int /*<<< orphan*/ * p_link_key_callback; } ;
struct TYPE_4__ {TYPE_1__ api; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__ btm_cb ; 

BOOLEAN BTM_SecRegisterLinkKeyNotificationCallback (tBTM_LINK_KEY_CALLBACK *p_callback)
{
    btm_cb.api.p_link_key_callback = p_callback;
    return TRUE;
}