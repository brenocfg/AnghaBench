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
struct TYPE_5__ {TYPE_1__* HEVClc; } ;
struct TYPE_4__ {int /*<<< orphan*/  cc; } ;
typedef  TYPE_2__ HEVCContext ;

/* Variables and functions */
 int get_cabac_terminate (int /*<<< orphan*/ *) ; 

int ff_hevc_end_of_slice_flag_decode(HEVCContext *s)
{
    return get_cabac_terminate(&s->HEVClc->cc);
}