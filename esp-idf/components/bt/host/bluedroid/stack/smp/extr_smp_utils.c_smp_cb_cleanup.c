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
struct TYPE_4__ {int /*<<< orphan*/  static_passkey; scalar_t__ use_static_passkey; int /*<<< orphan*/  trace_level; int /*<<< orphan*/ * p_callback; } ;
typedef  TYPE_1__ tSMP_CB ;
typedef  int /*<<< orphan*/  tSMP_CALLBACK ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  SMP_TRACE_EVENT (char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void smp_cb_cleanup(tSMP_CB *p_cb)
{
    tSMP_CALLBACK   *p_callback = p_cb->p_callback;
    UINT8           trace_level = p_cb->trace_level;
    UINT32          static_passkey = p_cb->static_passkey;
    BOOLEAN         use_static_passkey = p_cb->use_static_passkey;
    SMP_TRACE_EVENT("smp_cb_cleanup\n");

    memset(p_cb, 0, sizeof(tSMP_CB));
    p_cb->p_callback = p_callback;
    p_cb->trace_level = trace_level;
    if(use_static_passkey) {
        p_cb->use_static_passkey = use_static_passkey;
        p_cb->static_passkey = static_passkey;
    }
}