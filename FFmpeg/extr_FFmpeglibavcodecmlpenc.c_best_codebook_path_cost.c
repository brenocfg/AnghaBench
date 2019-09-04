#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int bitcount; } ;
struct TYPE_10__ {TYPE_3__*** best_offset; } ;
struct TYPE_9__ {int bitcount; char* path; } ;
typedef  TYPE_1__ PathCounter ;
typedef  TYPE_2__ MLPEncodeContext ;
typedef  TYPE_3__ BestOffset ;

/* Variables and functions */
 scalar_t__ CODEBOOK_CHANGE_BITS ; 
 char ZERO_PATH ; 
 scalar_t__ compare_best_offset (TYPE_3__*,TYPE_3__*) ; 
 TYPE_3__* restart_best_offset ; 

__attribute__((used)) static int best_codebook_path_cost(MLPEncodeContext *ctx, unsigned int channel,
                                   PathCounter *src, int cur_codebook)
{
    BestOffset *cur_bo, *prev_bo = restart_best_offset;
    int bitcount = src->bitcount;
    char *path = src->path + 1;
    int prev_codebook;
    int i;

    for (i = 0; path[i]; i++)
        prev_bo = ctx->best_offset[i][channel];

    prev_codebook = path[i - 1] - ZERO_PATH;

    cur_bo = ctx->best_offset[i][channel];

    bitcount += cur_bo[cur_codebook].bitcount;

    if (prev_codebook != cur_codebook ||
        compare_best_offset(&prev_bo[prev_codebook], &cur_bo[cur_codebook]))
        bitcount += CODEBOOK_CHANGE_BITS;

    return bitcount;
}