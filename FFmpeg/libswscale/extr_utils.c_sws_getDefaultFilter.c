#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * chrV; int /*<<< orphan*/ * chrH; int /*<<< orphan*/ * lumV; int /*<<< orphan*/ * lumH; } ;
typedef  int /*<<< orphan*/  SwsVector ;
typedef  TYPE_1__ SwsFilter ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 TYPE_1__* av_malloc (int) ; 
 scalar_t__ isnan_vec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sws_addVec (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sws_freeVec (int /*<<< orphan*/ *) ; 
 void* sws_getGaussianVec (float,double) ; 
 void* sws_getIdentityVec () ; 
 int /*<<< orphan*/  sws_normalizeVec (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  sws_printVec2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sws_scaleVec (int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  sws_shiftVec (int /*<<< orphan*/ *,int) ; 

SwsFilter *sws_getDefaultFilter(float lumaGBlur, float chromaGBlur,
                                float lumaSharpen, float chromaSharpen,
                                float chromaHShift, float chromaVShift,
                                int verbose)
{
    SwsFilter *filter = av_malloc(sizeof(SwsFilter));
    if (!filter)
        return NULL;

    if (lumaGBlur != 0.0) {
        filter->lumH = sws_getGaussianVec(lumaGBlur, 3.0);
        filter->lumV = sws_getGaussianVec(lumaGBlur, 3.0);
    } else {
        filter->lumH = sws_getIdentityVec();
        filter->lumV = sws_getIdentityVec();
    }

    if (chromaGBlur != 0.0) {
        filter->chrH = sws_getGaussianVec(chromaGBlur, 3.0);
        filter->chrV = sws_getGaussianVec(chromaGBlur, 3.0);
    } else {
        filter->chrH = sws_getIdentityVec();
        filter->chrV = sws_getIdentityVec();
    }

    if (!filter->lumH || !filter->lumV || !filter->chrH || !filter->chrV)
        goto fail;

    if (chromaSharpen != 0.0) {
        SwsVector *id = sws_getIdentityVec();
        if (!id)
            goto fail;
        sws_scaleVec(filter->chrH, -chromaSharpen);
        sws_scaleVec(filter->chrV, -chromaSharpen);
        sws_addVec(filter->chrH, id);
        sws_addVec(filter->chrV, id);
        sws_freeVec(id);
    }

    if (lumaSharpen != 0.0) {
        SwsVector *id = sws_getIdentityVec();
        if (!id)
            goto fail;
        sws_scaleVec(filter->lumH, -lumaSharpen);
        sws_scaleVec(filter->lumV, -lumaSharpen);
        sws_addVec(filter->lumH, id);
        sws_addVec(filter->lumV, id);
        sws_freeVec(id);
    }

    if (chromaHShift != 0.0)
        sws_shiftVec(filter->chrH, (int)(chromaHShift + 0.5));

    if (chromaVShift != 0.0)
        sws_shiftVec(filter->chrV, (int)(chromaVShift + 0.5));

    sws_normalizeVec(filter->chrH, 1.0);
    sws_normalizeVec(filter->chrV, 1.0);
    sws_normalizeVec(filter->lumH, 1.0);
    sws_normalizeVec(filter->lumV, 1.0);

    if (isnan_vec(filter->chrH) ||
        isnan_vec(filter->chrV) ||
        isnan_vec(filter->lumH) ||
        isnan_vec(filter->lumV))
        goto fail;

    if (verbose)
        sws_printVec2(filter->chrH, NULL, AV_LOG_DEBUG);
    if (verbose)
        sws_printVec2(filter->lumH, NULL, AV_LOG_DEBUG);

    return filter;

fail:
    sws_freeVec(filter->lumH);
    sws_freeVec(filter->lumV);
    sws_freeVec(filter->chrH);
    sws_freeVec(filter->chrV);
    av_freep(&filter);
    return NULL;
}