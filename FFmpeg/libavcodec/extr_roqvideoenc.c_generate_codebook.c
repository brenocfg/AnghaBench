#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int u; int v; int /*<<< orphan*/ * y; } ;
typedef  TYPE_1__ roq_cell ;
struct TYPE_9__ {int /*<<< orphan*/  randctx; } ;
struct TYPE_8__ {int* closest_cb2; } ;
typedef  TYPE_2__ RoqTempdata ;
typedef  TYPE_3__ RoqContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int CHROMA_BIAS ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_free (int*) ; 
 int* av_malloc_array (int,int) ; 
 int avpriv_do_elbg (int*,int,int,int*,int,int,int*,int /*<<< orphan*/ *) ; 
 int avpriv_init_elbg (int*,int,int,int*,int,int,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int generate_codebook(RoqContext *enc, RoqTempdata *tempdata,
                             int *points, int inputCount, roq_cell *results,
                             int size, int cbsize)
{
    int i, j, k, ret = 0;
    int c_size = size*size/4;
    int *buf;
    int *codebook = av_malloc_array(6*c_size, cbsize*sizeof(int));
    int *closest_cb;

    if (!codebook)
        return AVERROR(ENOMEM);

    if (size == 4) {
        closest_cb = av_malloc_array(6*c_size, inputCount*sizeof(int));
        if (!closest_cb) {
            ret = AVERROR(ENOMEM);
            goto out;
        }
    } else
        closest_cb = tempdata->closest_cb2;

    ret = avpriv_init_elbg(points, 6 * c_size, inputCount, codebook,
                       cbsize, 1, closest_cb, &enc->randctx);
    if (ret < 0)
        goto out;
    ret = avpriv_do_elbg(points, 6 * c_size, inputCount, codebook,
                     cbsize, 1, closest_cb, &enc->randctx);
    if (ret < 0)
        goto out;

    buf = codebook;
    for (i=0; i<cbsize; i++)
        for (k=0; k<c_size; k++) {
            for(j=0; j<4; j++)
                results->y[j] = *buf++;

            results->u =    (*buf++ + CHROMA_BIAS/2)/CHROMA_BIAS;
            results->v =    (*buf++ + CHROMA_BIAS/2)/CHROMA_BIAS;
            results++;
        }
out:
    if (size == 4)
        av_free(closest_cb);
    av_free(codebook);
    return ret;
}