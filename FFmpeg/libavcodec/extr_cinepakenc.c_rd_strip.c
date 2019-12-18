#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_13__ {int v1_size; int v4_size; scalar_t__ mode; } ;
typedef  TYPE_1__ strip_info ;
typedef  scalar_t__ int64_t ;
struct TYPE_14__ {int max_extra_cb_iterations; scalar_t__ strip_buf; } ;
typedef  scalar_t__ CinepakMode ;
typedef  TYPE_2__ CinepakEncContext ;

/* Variables and functions */
 int CODEBOOK_MAX ; 
 int /*<<< orphan*/  ENC_UNCERTAIN ; 
 int /*<<< orphan*/  ENC_V1 ; 
 int /*<<< orphan*/  ENC_V4 ; 
 scalar_t__ MODE_COUNT ; 
 scalar_t__ MODE_MC ; 
 scalar_t__ MODE_V1_ONLY ; 
 scalar_t__ MODE_V1_V4 ; 
 int SMALLEST_CODEBOOK ; 
 scalar_t__ STRIP_HEADER_SIZE ; 
 scalar_t__ calculate_mode_score (TYPE_2__*,int,TYPE_1__*,int,int*,int*) ; 
 int /*<<< orphan*/  calculate_skip_errors (TYPE_2__*,int,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ **,int*,TYPE_1__*) ; 
 int encode_mode (TYPE_2__*,int,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ **,int*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,scalar_t__,int) ; 
 void* quantize (TYPE_2__*,int,int /*<<< orphan*/ **,int*,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_strip_header (TYPE_2__*,int,int,int,scalar_t__,int) ; 

__attribute__((used)) static int rd_strip(CinepakEncContext *s, int y, int h, int keyframe,
                    uint8_t *last_data[4], int last_linesize[4],
                    uint8_t *data[4], int linesize[4],
                    uint8_t *scratch_data[4], int scratch_linesize[4],
                    unsigned char *buf, int64_t *best_score)
{
    int64_t score = 0;
    int best_size = 0;
    strip_info info;
    // for codebook optimization:
    int v1enough, v1_size, v4enough, v4_size;
    int new_v1_size, new_v4_size;
    int v1shrunk, v4shrunk;

    if (!keyframe)
        calculate_skip_errors(s, h, last_data, last_linesize, data, linesize,
                              &info);

    // try some powers of 4 for the size of the codebooks
    // constraint the v4 codebook to be no bigger than v1 one,
    // (and no less than v1_size/4)
    // thus making v1 preferable and possibly losing small details? should be ok
#define SMALLEST_CODEBOOK 1
    for (v1enough = 0, v1_size = SMALLEST_CODEBOOK; v1_size <= CODEBOOK_MAX && !v1enough; v1_size <<= 2) {
        for (v4enough = 0, v4_size = 0; v4_size <= v1_size && !v4enough; v4_size = v4_size ? v4_size << 2 : v1_size >= SMALLEST_CODEBOOK << 2 ? v1_size >> 2 : SMALLEST_CODEBOOK) {
            CinepakMode mode;
            // try all modes
            for (mode = 0; mode < MODE_COUNT; mode++) {
                // don't allow MODE_MC in intra frames
                if (keyframe && mode == MODE_MC)
                    continue;

                if (mode == MODE_V1_ONLY) {
                    info.v1_size = v1_size;
                    // the size may shrink even before optimizations if the input is short:
                    info.v1_size = quantize(s, h, data, linesize, 1,
                                            &info, ENC_UNCERTAIN);
                    if (info.v1_size < v1_size)
                        // too few eligible blocks, no sense in trying bigger sizes
                        v1enough = 1;

                    info.v4_size = 0;
                } else { // mode != MODE_V1_ONLY
                    // if v4 codebook is empty then only allow V1-only mode
                    if (!v4_size)
                        continue;

                    if (mode == MODE_V1_V4) {
                        info.v4_size = v4_size;
                        info.v4_size = quantize(s, h, data, linesize, 0,
                                                &info, ENC_UNCERTAIN);
                        if (info.v4_size < v4_size)
                            // too few eligible blocks, no sense in trying bigger sizes
                            v4enough = 1;
                    }
                }

                info.mode = mode;
                // choose the best encoding per block, based on current experience
                score = calculate_mode_score(s, h, &info, 0,
                                             &v1shrunk, &v4shrunk);

                if (mode != MODE_V1_ONLY) {
                    int extra_iterations_limit = s->max_extra_cb_iterations;
                    // recompute the codebooks, omitting the extra blocks
                    // we assume we _may_ come here with more blocks to encode than before
                    info.v1_size = v1_size;
                    new_v1_size = quantize(s, h, data, linesize, 1, &info, ENC_V1);
                    if (new_v1_size < info.v1_size)
                        info.v1_size = new_v1_size;
                    // we assume we _may_ come here with more blocks to encode than before
                    info.v4_size = v4_size;
                    new_v4_size = quantize(s, h, data, linesize, 0, &info, ENC_V4);
                    if (new_v4_size < info.v4_size)
                        info.v4_size = new_v4_size;
                    // calculate the resulting score
                    // (do not move blocks to codebook encodings now, as some blocks may have
                    // got bigger errors despite a smaller training set - but we do not
                    // ever grow the training sets back)
                    for (;;) {
                        score = calculate_mode_score(s, h, &info, 1,
                                                     &v1shrunk, &v4shrunk);
                        // do we have a reason to reiterate? if so, have we reached the limit?
                        if ((!v1shrunk && !v4shrunk) || !extra_iterations_limit--)
                            break;
                        // recompute the codebooks, omitting the extra blocks
                        if (v1shrunk) {
                            info.v1_size = v1_size;
                            new_v1_size = quantize(s, h, data, linesize, 1, &info, ENC_V1);
                            if (new_v1_size < info.v1_size)
                                info.v1_size = new_v1_size;
                        }
                        if (v4shrunk) {
                            info.v4_size = v4_size;
                            new_v4_size = quantize(s, h, data, linesize, 0, &info, ENC_V4);
                            if (new_v4_size < info.v4_size)
                                info.v4_size = new_v4_size;
                        }
                    }
                }

                if (best_size == 0 || score < *best_score) {
                    *best_score = score;
                    best_size = encode_mode(s, h,
                                            scratch_data, scratch_linesize,
                                            last_data, last_linesize, &info,
                                            s->strip_buf + STRIP_HEADER_SIZE);

                    write_strip_header(s, y, h, keyframe, s->strip_buf, best_size);
                }
            }
        }
    }

    best_size += STRIP_HEADER_SIZE;
    memcpy(buf, s->strip_buf, best_size);

    return best_size;
}