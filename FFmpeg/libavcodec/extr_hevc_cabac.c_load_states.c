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
struct TYPE_5__ {int /*<<< orphan*/  cabac_state; TYPE_1__* HEVClc; } ;
struct TYPE_4__ {int /*<<< orphan*/  cabac_state; } ;
typedef  TYPE_2__ HEVCContext ;

/* Variables and functions */
 int /*<<< orphan*/  HEVC_CONTEXTS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void load_states(HEVCContext *s)
{
    memcpy(s->HEVClc->cabac_state, s->cabac_state, HEVC_CONTEXTS);
}