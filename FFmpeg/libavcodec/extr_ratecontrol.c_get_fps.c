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
struct TYPE_3__ {int /*<<< orphan*/  ticks_per_frame; int /*<<< orphan*/  time_base; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 double FFMAX (int /*<<< orphan*/ ,int) ; 
 double av_q2d (int /*<<< orphan*/ ) ; 

__attribute__((used)) static double get_fps(AVCodecContext *avctx)
{
    return 1.0 / av_q2d(avctx->time_base) / FFMAX(avctx->ticks_per_frame, 1);
}