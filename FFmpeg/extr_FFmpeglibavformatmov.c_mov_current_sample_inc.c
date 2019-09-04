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
struct TYPE_5__ {scalar_t__ current_index; TYPE_1__* current_index_range; scalar_t__ index_ranges; int /*<<< orphan*/  current_sample; } ;
struct TYPE_4__ {scalar_t__ end; scalar_t__ start; } ;
typedef  TYPE_2__ MOVStreamContext ;

/* Variables and functions */

__attribute__((used)) static void mov_current_sample_inc(MOVStreamContext *sc)
{
    sc->current_sample++;
    sc->current_index++;
    if (sc->index_ranges &&
        sc->current_index >= sc->current_index_range->end &&
        sc->current_index_range->end) {
        sc->current_index_range++;
        sc->current_index = sc->current_index_range->start;
    }
}