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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;

/* Variables and functions */
 int AV_PIX_FMT_NONE ; 
 int FF_ARRAY_ELEMS (int /*<<< orphan*/ *) ; 
 int av_find_best_pix_fmt_of_2 (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pixfmt_list ; 

__attribute__((used)) static enum AVPixelFormat find_best(enum AVPixelFormat pixfmt)
{
    enum AVPixelFormat best = AV_PIX_FMT_NONE;
    int i;
    for (i = 0; i < FF_ARRAY_ELEMS(pixfmt_list); i++)
        best = av_find_best_pix_fmt_of_2(best, pixfmt_list[i],
                                         pixfmt, 0, NULL);
    return best;
}