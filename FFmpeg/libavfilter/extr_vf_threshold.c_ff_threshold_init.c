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
struct TYPE_4__ {int depth; int bpc; int /*<<< orphan*/  threshold; } ;
typedef  TYPE_1__ ThresholdContext ;

/* Variables and functions */
 scalar_t__ ARCH_X86 ; 
 int /*<<< orphan*/  ff_threshold_init_x86 (TYPE_1__*) ; 
 int /*<<< orphan*/  threshold16 ; 
 int /*<<< orphan*/  threshold8 ; 

void ff_threshold_init(ThresholdContext *s)
{
    if (s->depth == 8) {
        s->threshold = threshold8;
        s->bpc = 1;
    } else {
        s->threshold = threshold16;
        s->bpc = 2;
    }

    if (ARCH_X86)
        ff_threshold_init_x86(s);
}