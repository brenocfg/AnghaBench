#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  enum test_type { ____Placeholder_test_type } test_type ;
struct TYPE_13__ {unsigned int frame_count_in; TYPE_1__* src; } ;
struct TYPE_12__ {int* linesize; scalar_t__* data; scalar_t__ pts; } ;
struct TYPE_11__ {scalar_t__ max_pts; scalar_t__ pts; int /*<<< orphan*/  test; int /*<<< orphan*/  vsub; int /*<<< orphan*/  hsub; } ;
struct TYPE_10__ {TYPE_2__* priv; } ;
typedef  TYPE_2__ MPTestContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterLink ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AV_CEIL_RSHIFT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int HEIGHT ; 
 int TEST_ALL ; 
#define  TEST_AMP_CHROMA 137 
#define  TEST_AMP_LUMA 136 
#define  TEST_CBP 135 
#define  TEST_DC_CHROMA 134 
#define  TEST_DC_LUMA 133 
#define  TEST_FREQ_CHROMA 132 
#define  TEST_FREQ_LUMA 131 
#define  TEST_MV 130 
 int TEST_NB ; 
#define  TEST_RING1 129 
#define  TEST_RING2 128 
 int WIDTH ; 
 int /*<<< orphan*/  amp_test (scalar_t__,int,unsigned int) ; 
 int /*<<< orphan*/  cbp_test (scalar_t__*,int*,unsigned int) ; 
 int /*<<< orphan*/  dc_test (scalar_t__,int,int,int,unsigned int) ; 
 int ff_filter_frame (TYPE_4__*,TYPE_3__*) ; 
 TYPE_3__* ff_get_video_buffer (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  freq_test (scalar_t__,int,unsigned int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int,int) ; 
 int /*<<< orphan*/  mv_test (scalar_t__,int,unsigned int) ; 
 int /*<<< orphan*/  ring1_test (scalar_t__,int,unsigned int) ; 
 int /*<<< orphan*/  ring2_test (scalar_t__,int,unsigned int) ; 

__attribute__((used)) static int request_frame(AVFilterLink *outlink)
{
    MPTestContext *test = outlink->src->priv;
    AVFrame *picref;
    int w = WIDTH, h = HEIGHT,
        cw = AV_CEIL_RSHIFT(w, test->hsub), ch = AV_CEIL_RSHIFT(h, test->vsub);
    unsigned int frame = outlink->frame_count_in;
    enum test_type tt = test->test;
    int i;

    if (test->max_pts >= 0 && test->pts > test->max_pts)
        return AVERROR_EOF;
    picref = ff_get_video_buffer(outlink, w, h);
    if (!picref)
        return AVERROR(ENOMEM);
    picref->pts = test->pts++;

    // clean image
    for (i = 0; i < h; i++)
        memset(picref->data[0] + i*picref->linesize[0], 0, w);
    for (i = 0; i < ch; i++) {
        memset(picref->data[1] + i*picref->linesize[1], 128, cw);
        memset(picref->data[2] + i*picref->linesize[2], 128, cw);
    }

    if (tt == TEST_ALL && frame%30) /* draw a black frame at the beginning of each test */
        tt = (frame/30)%(TEST_NB-1);

    switch (tt) {
    case TEST_DC_LUMA:       dc_test(picref->data[0], picref->linesize[0], 256, 256, frame%30); break;
    case TEST_DC_CHROMA:     dc_test(picref->data[1], picref->linesize[1], 256, 256, frame%30); break;
    case TEST_FREQ_LUMA:   freq_test(picref->data[0], picref->linesize[0], frame%30); break;
    case TEST_FREQ_CHROMA: freq_test(picref->data[1], picref->linesize[1], frame%30); break;
    case TEST_AMP_LUMA:     amp_test(picref->data[0], picref->linesize[0], frame%30); break;
    case TEST_AMP_CHROMA:   amp_test(picref->data[1], picref->linesize[1], frame%30); break;
    case TEST_CBP:          cbp_test(picref->data   , picref->linesize   , frame%30); break;
    case TEST_MV:            mv_test(picref->data[0], picref->linesize[0], frame%30); break;
    case TEST_RING1:      ring1_test(picref->data[0], picref->linesize[0], frame%30); break;
    case TEST_RING2:      ring2_test(picref->data[0], picref->linesize[0], frame%30); break;
    }

    return ff_filter_frame(outlink, picref);
}