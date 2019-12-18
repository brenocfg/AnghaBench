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
struct TYPE_3__ {int use_static_passkey; scalar_t__ static_passkey; } ;
typedef  TYPE_1__ tSMP_CB ;
typedef  scalar_t__ UINT32 ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  SMP_TRACE_DEBUG (char*,scalar_t__) ; 
 TYPE_1__ smp_cb ; 

void SMP_SetStaticPasskey (BOOLEAN add, UINT32 passkey)
{
    SMP_TRACE_DEBUG("static passkey %6d", passkey);
    tSMP_CB *p_cb = & smp_cb;
    if(add) {
        p_cb->static_passkey = passkey;
        p_cb->use_static_passkey = true;
    } else {
        p_cb->static_passkey = 0;
        p_cb->use_static_passkey = false;
    }
}