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
struct TYPE_3__ {float* cscheme_v; int /*<<< orphan*/  ctx; int /*<<< orphan*/  cscheme; } ;
typedef  TYPE_1__ ShowCQTContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isnan (float) ; 
 int sscanf (int /*<<< orphan*/ ,char*,float*,float*,float*,float*,float*,float*,char*) ; 

__attribute__((used)) static int init_cscheme(ShowCQTContext *s)
{
    char tail[2];
    int k;

    if (sscanf(s->cscheme, " %f | %f | %f | %f | %f | %f %1s", &s->cscheme_v[0],
        &s->cscheme_v[1], &s->cscheme_v[2], &s->cscheme_v[3], &s->cscheme_v[4],
        &s->cscheme_v[5], tail) != 6)
        goto fail;

    for (k = 0; k < 6; k++)
        if (isnan(s->cscheme_v[k]) || s->cscheme_v[k] < 0.0f || s->cscheme_v[k] > 1.0f)
            goto fail;

    return 0;

fail:
    av_log(s->ctx, AV_LOG_ERROR, "invalid cscheme.\n");
    return AVERROR(EINVAL);
}