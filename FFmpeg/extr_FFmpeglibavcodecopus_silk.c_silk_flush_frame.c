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
struct TYPE_3__ {scalar_t__ coded; scalar_t__ prev_voiced; scalar_t__ primarylag; scalar_t__ log_gain; int /*<<< orphan*/  nlsf; int /*<<< orphan*/  lpc; int /*<<< orphan*/  lpc_history; int /*<<< orphan*/  output; } ;
typedef  TYPE_1__ SilkFrame ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void silk_flush_frame(SilkFrame *frame)
{
    if (!frame->coded)
        return;

    memset(frame->output,      0, sizeof(frame->output));
    memset(frame->lpc_history, 0, sizeof(frame->lpc_history));

    memset(frame->lpc,  0, sizeof(frame->lpc));
    memset(frame->nlsf, 0, sizeof(frame->nlsf));

    frame->log_gain = 0;

    frame->primarylag  = 0;
    frame->prev_voiced = 0;
    frame->coded       = 0;
}