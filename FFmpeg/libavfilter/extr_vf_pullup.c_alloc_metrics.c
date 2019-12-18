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
struct TYPE_6__ {int /*<<< orphan*/  metric_length; } ;
struct TYPE_5__ {void* vars; void* combs; void* diffs; } ;
typedef  TYPE_1__ PullupField ;
typedef  TYPE_2__ PullupContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFALIGN (int /*<<< orphan*/ ,int) ; 
 void* av_calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_freep (void**) ; 

__attribute__((used)) static int alloc_metrics(PullupContext *s, PullupField *f)
{
    f->diffs = av_calloc(FFALIGN(s->metric_length, 16), sizeof(*f->diffs));
    f->combs = av_calloc(FFALIGN(s->metric_length, 16), sizeof(*f->combs));
    f->vars  = av_calloc(FFALIGN(s->metric_length, 16), sizeof(*f->vars));

    if (!f->diffs || !f->combs || !f->vars) {
        av_freep(&f->diffs);
        av_freep(&f->combs);
        av_freep(&f->vars);
        return AVERROR(ENOMEM);
    }
    return 0;
}