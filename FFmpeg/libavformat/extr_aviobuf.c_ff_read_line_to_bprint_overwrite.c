#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {scalar_t__ len; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVBPrint ;

/* Variables and functions */
 scalar_t__ AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_bprint_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  av_bprint_is_complete (TYPE_1__*) ; 
 scalar_t__ ff_read_line_to_bprint (int /*<<< orphan*/ *,TYPE_1__*) ; 

int64_t ff_read_line_to_bprint_overwrite(AVIOContext *s, AVBPrint *bp)
{
    int64_t ret;

    av_bprint_clear(bp);
    ret = ff_read_line_to_bprint(s, bp);
    if (ret < 0)
        return ret;

    if (!av_bprint_is_complete(bp))
        return AVERROR(ENOMEM);

    return bp->len;
}