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
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;

/* Variables and functions */
 int get_fmt_score (int,int) ; 

__attribute__((used)) static enum AVSampleFormat find_best_sample_fmt_of_2(enum AVSampleFormat dst_fmt1, enum AVSampleFormat dst_fmt2,
                                                     enum AVSampleFormat src_fmt)
{
    int score1, score2;

    score1 = get_fmt_score(dst_fmt1, src_fmt);
    score2 = get_fmt_score(dst_fmt2, src_fmt);

    return score1 < score2 ? dst_fmt1 : dst_fmt2;
}