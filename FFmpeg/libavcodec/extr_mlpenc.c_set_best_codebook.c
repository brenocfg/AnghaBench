#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {scalar_t__ lsb_bits; int /*<<< orphan*/  offset; } ;
struct TYPE_22__ {unsigned int codebook; scalar_t__ huff_lsbs; int /*<<< orphan*/  huff_offset; } ;
struct TYPE_21__ {scalar_t__* quant_step_size; } ;
struct TYPE_20__ {unsigned int number_of_subblocks; TYPE_7__*** best_offset; TYPE_1__* avctx; TYPE_6__* seq_channel_params; TYPE_2__* cur_restart_header; TYPE_5__* cur_decoding_params; } ;
struct TYPE_19__ {char* path; int bitcount; } ;
struct TYPE_18__ {unsigned int min_channel; unsigned int max_channel; } ;
struct TYPE_17__ {unsigned int channels; } ;
typedef  TYPE_2__ RestartHeader ;
typedef  TYPE_3__ PathCounter ;
typedef  TYPE_4__ MLPEncodeContext ;
typedef  TYPE_5__ DecodingParams ;
typedef  TYPE_6__ ChannelParams ;
typedef  TYPE_7__ BestOffset ;

/* Variables and functions */
 void* INT_MAX ; 
 int NUM_CODEBOOKS ; 
 unsigned int ZERO_PATH ; 
 int /*<<< orphan*/  av_strlcat (char*,int /*<<< orphan*/ ,int) ; 
 int best_codebook_path_cost (TYPE_4__*,unsigned int,TYPE_3__*,unsigned int) ; 
 int /*<<< orphan*/  clear_path_counter (TYPE_3__*) ; 
 scalar_t__ compare_best_offset (TYPE_7__*,TYPE_7__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/ * path_counter_codebook ; 
 TYPE_7__* restart_best_offset ; 

__attribute__((used)) static void set_best_codebook(MLPEncodeContext *ctx)
{
    DecodingParams *dp = ctx->cur_decoding_params;
    RestartHeader *rh = ctx->cur_restart_header;
    unsigned int channel;

    for (channel = rh->min_channel; channel <= rh->max_channel; channel++) {
        BestOffset *cur_bo, *prev_bo = restart_best_offset;
        PathCounter path_counter[NUM_CODEBOOKS + 1];
        unsigned int best_codebook;
        unsigned int index;
        char *best_path;

        clear_path_counter(path_counter);

        for (index = 0; index < ctx->number_of_subblocks; index++) {
            unsigned int best_bitcount = INT_MAX;
            unsigned int codebook;

            cur_bo = ctx->best_offset[index][channel];

            for (codebook = 0; codebook < NUM_CODEBOOKS; codebook++) {
                int prev_best_bitcount = INT_MAX;
                int last_best;

                for (last_best = 0; last_best < 2; last_best++) {
                    PathCounter *dst_path = &path_counter[codebook];
                    PathCounter *src_path;
                    int  temp_bitcount;

                    /* First test last path with same headers,
                     * then with last best. */
                    if (last_best) {
                        src_path = &path_counter[NUM_CODEBOOKS];
                    } else {
                        if (compare_best_offset(&prev_bo[codebook], &cur_bo[codebook]))
                            continue;
                        else
                            src_path = &path_counter[codebook];
                    }

                    temp_bitcount = best_codebook_path_cost(ctx, channel, src_path, codebook);

                    if (temp_bitcount < best_bitcount) {
                        best_bitcount = temp_bitcount;
                        best_codebook = codebook;
                    }

                    if (temp_bitcount < prev_best_bitcount) {
                        prev_best_bitcount = temp_bitcount;
                        if (src_path != dst_path)
                            memcpy(dst_path, src_path, sizeof(PathCounter));
                        av_strlcat(dst_path->path, path_counter_codebook[codebook], sizeof(dst_path->path));
                        dst_path->bitcount = temp_bitcount;
                    }
                }
            }

            prev_bo = cur_bo;

            memcpy(&path_counter[NUM_CODEBOOKS], &path_counter[best_codebook], sizeof(PathCounter));
        }

        best_path = path_counter[NUM_CODEBOOKS].path + 1;

        /* Update context. */
        for (index = 0; index < ctx->number_of_subblocks; index++) {
            ChannelParams *cp = ctx->seq_channel_params + index*(ctx->avctx->channels) + channel;

            best_codebook = *best_path++ - ZERO_PATH;
            cur_bo = &ctx->best_offset[index][channel][best_codebook];

            cp->huff_offset = cur_bo->offset;
            cp->huff_lsbs   = cur_bo->lsb_bits + dp->quant_step_size[channel];
            cp->codebook    = best_codebook;
        }
    }
}