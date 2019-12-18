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
typedef  int /*<<< orphan*/  SwsFilter ;
typedef  int /*<<< orphan*/  SwsContext ;

/* Variables and functions */
 int /*<<< orphan*/ * sws_alloc_set_opts (int,int,int,int,int,int,int,double const*) ; 
 int /*<<< orphan*/  sws_freeContext (int /*<<< orphan*/ *) ; 
 scalar_t__ sws_init_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

SwsContext *sws_getContext(int srcW, int srcH, enum AVPixelFormat srcFormat,
                           int dstW, int dstH, enum AVPixelFormat dstFormat,
                           int flags, SwsFilter *srcFilter,
                           SwsFilter *dstFilter, const double *param)
{
    SwsContext *c;

    c = sws_alloc_set_opts(srcW, srcH, srcFormat,
                           dstW, dstH, dstFormat,
                           flags, param);
    if (!c)
        return NULL;

    if (sws_init_context(c, srcFilter, dstFilter) < 0) {
        sws_freeContext(c);
        return NULL;
    }

    return c;
}