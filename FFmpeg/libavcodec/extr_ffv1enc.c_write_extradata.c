#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  state2 ;
typedef  int /*<<< orphan*/  state ;
typedef  int int8_t ;
struct TYPE_12__ {int* one_state; } ;
struct TYPE_13__ {int version; int micro_version; int ac; int* state_transition; int colorspace; int bits_per_raw_sample; int chroma_planes; int chroma_h_shift; int chroma_v_shift; int transparency; int num_h_slices; int num_v_slices; int quant_table_count; int*** initial_states; int* context_count; int ec; int intra; TYPE_1__* avctx; int /*<<< orphan*/ * quant_tables; TYPE_2__ c; } ;
struct TYPE_11__ {int extradata_size; int extradata; int gop_size; } ;
typedef  TYPE_2__ RangeCoder ;
typedef  TYPE_3__ FFV1Context ;

/* Variables and functions */
 int AC_RANGE_CUSTOM_TAB ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_CRC_32_IEEE ; 
 int AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_WL32 (int,unsigned int) ; 
 int CONTEXT_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 unsigned int av_crc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  av_crc_get_table (int /*<<< orphan*/ ) ; 
 int av_malloc (int) ; 
 scalar_t__ contains_non_128 (int**,int) ; 
 int /*<<< orphan*/  ff_build_rac_states (TYPE_2__* const,double,int) ; 
 int /*<<< orphan*/  ff_init_range_encoder (TYPE_2__* const,int,int) ; 
 int ff_rac_terminate (TYPE_2__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_rac (TYPE_2__* const,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_symbol (TYPE_2__* const,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  write_quant_tables (TYPE_2__* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_extradata(FFV1Context *f)
{
    RangeCoder *const c = &f->c;
    uint8_t state[CONTEXT_SIZE];
    int i, j, k;
    uint8_t state2[32][CONTEXT_SIZE];
    unsigned v;

    memset(state2, 128, sizeof(state2));
    memset(state, 128, sizeof(state));

    f->avctx->extradata_size = 10000 + 4 +
                                    (11 * 11 * 5 * 5 * 5 + 11 * 11 * 11) * 32;
    f->avctx->extradata = av_malloc(f->avctx->extradata_size + AV_INPUT_BUFFER_PADDING_SIZE);
    if (!f->avctx->extradata)
        return AVERROR(ENOMEM);
    ff_init_range_encoder(c, f->avctx->extradata, f->avctx->extradata_size);
    ff_build_rac_states(c, 0.05 * (1LL << 32), 256 - 8);

    put_symbol(c, state, f->version, 0);
    if (f->version > 2) {
        if (f->version == 3) {
            f->micro_version = 4;
        } else if (f->version == 4)
            f->micro_version = 2;
        put_symbol(c, state, f->micro_version, 0);
    }

    put_symbol(c, state, f->ac, 0);
    if (f->ac == AC_RANGE_CUSTOM_TAB)
        for (i = 1; i < 256; i++)
            put_symbol(c, state, f->state_transition[i] - c->one_state[i], 1);

    put_symbol(c, state, f->colorspace, 0); // YUV cs type
    put_symbol(c, state, f->bits_per_raw_sample, 0);
    put_rac(c, state, f->chroma_planes);
    put_symbol(c, state, f->chroma_h_shift, 0);
    put_symbol(c, state, f->chroma_v_shift, 0);
    put_rac(c, state, f->transparency);
    put_symbol(c, state, f->num_h_slices - 1, 0);
    put_symbol(c, state, f->num_v_slices - 1, 0);

    put_symbol(c, state, f->quant_table_count, 0);
    for (i = 0; i < f->quant_table_count; i++)
        write_quant_tables(c, f->quant_tables[i]);

    for (i = 0; i < f->quant_table_count; i++) {
        if (contains_non_128(f->initial_states[i], f->context_count[i])) {
            put_rac(c, state, 1);
            for (j = 0; j < f->context_count[i]; j++)
                for (k = 0; k < CONTEXT_SIZE; k++) {
                    int pred = j ? f->initial_states[i][j - 1][k] : 128;
                    put_symbol(c, state2[k],
                               (int8_t)(f->initial_states[i][j][k] - pred), 1);
                }
        } else {
            put_rac(c, state, 0);
        }
    }

    if (f->version > 2) {
        put_symbol(c, state, f->ec, 0);
        put_symbol(c, state, f->intra = (f->avctx->gop_size < 2), 0);
    }

    f->avctx->extradata_size = ff_rac_terminate(c, 0);
    v = av_crc(av_crc_get_table(AV_CRC_32_IEEE), 0, f->avctx->extradata, f->avctx->extradata_size);
    AV_WL32(f->avctx->extradata + f->avctx->extradata_size, v);
    f->avctx->extradata_size += 4;

    return 0;
}