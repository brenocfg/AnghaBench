#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  debug_matches; } ;
struct TYPE_5__ {int /*<<< orphan*/  matches; } ;
typedef  TYPE_1__ DebugMatches ;
typedef  TYPE_2__ AbsoluteFrameMotion ;

/* Variables and functions */
 int /*<<< orphan*/  av_fifo_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_fifo_generic_read (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ av_fifo_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_debug_matches(AbsoluteFrameMotion *afm) {
    DebugMatches dm;

    if (!afm->debug_matches) {
        return;
    }

    while (av_fifo_size(afm->debug_matches) > 0) {
        av_fifo_generic_read(
            afm->debug_matches,
            &dm,
            sizeof(DebugMatches),
            NULL
        );

        av_freep(&dm.matches);
    }

    av_fifo_freep(&afm->debug_matches);
}