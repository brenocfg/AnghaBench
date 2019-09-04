#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int pre_filter_linesize; double quality; int* color_diff_coeff; int dist_width; int dist_linesize; int* dist_coeff; int /*<<< orphan*/  radius; int /*<<< orphan*/  strength; int /*<<< orphan*/  pre_filter_context; int /*<<< orphan*/  pre_filter_radius; int /*<<< orphan*/  pre_filter_buf; } ;
struct TYPE_9__ {int /*<<< orphan*/ * chrV; int /*<<< orphan*/  chrH; TYPE_1__* lumV; TYPE_1__* lumH; } ;
struct TYPE_8__ {int length; double* coeff; } ;
typedef  TYPE_1__ SwsVector ;
typedef  TYPE_2__ SwsFilter ;
typedef  TYPE_3__ FilterParam ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_PIX_FMT_GRAY8 ; 
 int COLOR_DIFF_COEFF_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* FFALIGN (int,int) ; 
 int /*<<< orphan*/  av_malloc (int) ; 
 int* av_malloc_array (int,int) ; 
 int /*<<< orphan*/  sws_freeVec (TYPE_1__*) ; 
 int /*<<< orphan*/  sws_getContext (int,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,unsigned int,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* sws_getGaussianVec (int /*<<< orphan*/ ,double) ; 

__attribute__((used)) static int open_filter_param(FilterParam *f, int width, int height, unsigned int sws_flags)
{
    SwsVector *vec;
    SwsFilter sws_f;
    int i, x, y;
    int linesize = FFALIGN(width, 8);

    f->pre_filter_buf = av_malloc(linesize * height);
    if (!f->pre_filter_buf)
        return AVERROR(ENOMEM);

    f->pre_filter_linesize = linesize;
    vec = sws_getGaussianVec(f->pre_filter_radius, f->quality);
    sws_f.lumH = sws_f.lumV = vec;
    sws_f.chrH = sws_f.chrV = NULL;
    f->pre_filter_context = sws_getContext(width, height, AV_PIX_FMT_GRAY8,
                                           width, height, AV_PIX_FMT_GRAY8,
                                           sws_flags, &sws_f, NULL, NULL);
    sws_freeVec(vec);

    vec = sws_getGaussianVec(f->strength, 5.0);
    for (i = 0; i < COLOR_DIFF_COEFF_SIZE; i++) {
        double d;
        int index = i-COLOR_DIFF_COEFF_SIZE/2 + vec->length/2;

        if (index < 0 || index >= vec->length) d = 0.0;
        else                                   d = vec->coeff[index];

        f->color_diff_coeff[i] = (int)(d/vec->coeff[vec->length/2]*(1<<12) + 0.5);
    }
    sws_freeVec(vec);

    vec = sws_getGaussianVec(f->radius, f->quality);
    f->dist_width    = vec->length;
    f->dist_linesize = FFALIGN(vec->length, 8);
    f->dist_coeff    = av_malloc_array(f->dist_width, f->dist_linesize * sizeof(*f->dist_coeff));
    if (!f->dist_coeff) {
        sws_freeVec(vec);
        return AVERROR(ENOMEM);
    }

    for (y = 0; y < vec->length; y++) {
        for (x = 0; x < vec->length; x++) {
            double d = vec->coeff[x] * vec->coeff[y];
            f->dist_coeff[x + y*f->dist_linesize] = (int)(d*(1<<10) + 0.5);
        }
    }
    sws_freeVec(vec);

    return 0;
}