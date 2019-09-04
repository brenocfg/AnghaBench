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
struct TYPE_3__ {int /*<<< orphan*/  dist_coeff; int /*<<< orphan*/  pre_filter_buf; int /*<<< orphan*/ * pre_filter_context; } ;
typedef  TYPE_1__ FilterParam ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sws_freeContext (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_filter_param(FilterParam *f)
{
    if (f->pre_filter_context) {
        sws_freeContext(f->pre_filter_context);
        f->pre_filter_context = NULL;
    }
    av_freep(&f->pre_filter_buf);
    av_freep(&f->dist_coeff);
}