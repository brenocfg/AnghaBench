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
struct TYPE_3__ {int /*<<< orphan*/  prev_stereo_weights; int /*<<< orphan*/ * frame; } ;
typedef  TYPE_1__ SilkContext ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  silk_flush_frame (int /*<<< orphan*/ *) ; 

void ff_silk_flush(SilkContext *s)
{
    silk_flush_frame(&s->frame[0]);
    silk_flush_frame(&s->frame[1]);

    memset(s->prev_stereo_weights, 0, sizeof(s->prev_stereo_weights));
}