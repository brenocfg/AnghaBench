#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int roq_cell ;
struct TYPE_12__ {int /*<<< orphan*/ * idx; } ;
struct TYPE_11__ {int numCB4; int numCB2; int* unpacked_cb2; scalar_t__ unpacked_cb4_enlarged; scalar_t__ unpacked_cb4; } ;
struct TYPE_10__ {int width; int height; int* cb2x2; TYPE_4__* cb4x4; scalar_t__ quake3_compat; int /*<<< orphan*/  frame_to_enc; } ;
struct TYPE_9__ {void* closest_cb2; TYPE_3__ codebooks; } ;
typedef  TYPE_1__ RoqTempdata ;
typedef  TYPE_2__ RoqContext ;
typedef  TYPE_3__ RoqCodebooks ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int CHROMA_BIAS ; 
 int /*<<< orphan*/  ENOMEM ; 
 int MAX_CBS_2x2 ; 
 int MAX_CBS_4x4 ; 
 int /*<<< orphan*/  av_free (int*) ; 
 int* av_malloc (int) ; 
 void* av_malloc_array (int,int) ; 
 int /*<<< orphan*/  create_clusters (int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  enlarge_roq_mb4 (scalar_t__,scalar_t__) ; 
 int generate_codebook (TYPE_2__*,TYPE_1__*,int*,int,int*,int,int) ; 
 int /*<<< orphan*/  index_mb (int*,int*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  unpack_roq_cell (int*,int*) ; 
 int /*<<< orphan*/  unpack_roq_qcell (int*,TYPE_4__*,scalar_t__) ; 

__attribute__((used)) static int generate_new_codebooks(RoqContext *enc, RoqTempdata *tempData)
{
    int i, j, ret = 0;
    RoqCodebooks *codebooks = &tempData->codebooks;
    int max = enc->width*enc->height/16;
    uint8_t mb2[3*4];
    roq_cell *results4 = av_malloc(sizeof(roq_cell)*MAX_CBS_4x4*4);
    uint8_t *yuvClusters=av_malloc_array(max, sizeof(int)*6*4);
    int *points = av_malloc_array(max, 6*4*sizeof(int));
    int bias;

    if (!results4 || !yuvClusters || !points) {
        ret = AVERROR(ENOMEM);
        goto out;
    }

    /* Subsample YUV data */
    create_clusters(enc->frame_to_enc, enc->width, enc->height, yuvClusters);

    /* Cast to integer and apply chroma bias */
    for (i=0; i<max*24; i++) {
        bias = ((i%6)<4) ? 1 : CHROMA_BIAS;
        points[i] = bias*yuvClusters[i];
    }

    /* Create 4x4 codebooks */
    if ((ret = generate_codebook(enc, tempData, points, max,
                                 results4, 4, (enc->quake3_compat ? MAX_CBS_4x4-1 : MAX_CBS_4x4))) < 0)
        goto out;

    codebooks->numCB4 = (enc->quake3_compat ? MAX_CBS_4x4-1 : MAX_CBS_4x4);

    tempData->closest_cb2 = av_malloc_array(max, 4*sizeof(int));
    if (!tempData->closest_cb2) {
        ret = AVERROR(ENOMEM);
        goto out;
    }

    /* Create 2x2 codebooks */
    if ((ret = generate_codebook(enc, tempData, points, max * 4,
                                 enc->cb2x2, 2, MAX_CBS_2x2)) < 0)
        goto out;

    codebooks->numCB2 = MAX_CBS_2x2;

    /* Unpack 2x2 codebook clusters */
    for (i=0; i<codebooks->numCB2; i++)
        unpack_roq_cell(enc->cb2x2 + i, codebooks->unpacked_cb2 + i*2*2*3);

    /* Index all 4x4 entries to the 2x2 entries, unpack, and enlarge */
    for (i=0; i<codebooks->numCB4; i++) {
        for (j=0; j<4; j++) {
            unpack_roq_cell(&results4[4*i + j], mb2);
            index_mb(mb2, codebooks->unpacked_cb2, codebooks->numCB2,
                     &enc->cb4x4[i].idx[j], 2);
        }
        unpack_roq_qcell(codebooks->unpacked_cb2, enc->cb4x4 + i,
                         codebooks->unpacked_cb4 + i*4*4*3);
        enlarge_roq_mb4(codebooks->unpacked_cb4 + i*4*4*3,
                        codebooks->unpacked_cb4_enlarged + i*8*8*3);
    }
out:
    av_free(yuvClusters);
    av_free(points);
    av_free(results4);
    return ret;
}