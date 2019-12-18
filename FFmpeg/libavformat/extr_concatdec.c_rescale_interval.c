#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  AVRational ;

/* Variables and functions */
 int AV_ROUND_DOWN ; 
 int AV_ROUND_PASS_MINMAX ; 
 int AV_ROUND_UP ; 
 int /*<<< orphan*/  av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_rescale_q_rnd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rescale_interval(AVRational tb_in, AVRational tb_out,
                             int64_t *min_ts, int64_t *ts, int64_t *max_ts)
{
    *ts     = av_rescale_q    (*    ts, tb_in, tb_out);
    *min_ts = av_rescale_q_rnd(*min_ts, tb_in, tb_out,
                               AV_ROUND_UP   | AV_ROUND_PASS_MINMAX);
    *max_ts = av_rescale_q_rnd(*max_ts, tb_in, tb_out,
                               AV_ROUND_DOWN | AV_ROUND_PASS_MINMAX);
}