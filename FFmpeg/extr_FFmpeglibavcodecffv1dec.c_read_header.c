#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  unsigned int uint64_t ;
typedef  int /*<<< orphan*/  state ;
struct TYPE_13__ {int bits_per_raw_sample; scalar_t__ pix_fmt; scalar_t__ skip_alpha; } ;
struct TYPE_10__ {int* one_state; int /*<<< orphan*/  const* bytestream_start; int /*<<< orphan*/ * bytestream_end; } ;
struct TYPE_12__ {int version; int ac; int* state_transition; int plane_count; int colorspace; int chroma_planes; int chroma_h_shift; int chroma_v_shift; int transparency; int packed_at_lsb; int use32bit; int slice_count; int max_slice_count; int slice_x; int width; int slice_y; int height; int slice_width; int slice_height; int num_h_slices; int num_v_slices; int* context_count; int /*<<< orphan*/  quant_table; int /*<<< orphan*/ * quant_tables; TYPE_8__* avctx; scalar_t__ quant_table_count; TYPE_2__* plane; scalar_t__ slice_damaged; struct TYPE_12__** slice_context; int /*<<< orphan*/  ec; TYPE_1__ c; } ;
struct TYPE_11__ {int quant_table_index; int context_count; int /*<<< orphan*/  vlc_state; int /*<<< orphan*/  state; int /*<<< orphan*/  quant_table; } ;
typedef  TYPE_1__ RangeCoder ;
typedef  TYPE_2__ PlaneContext ;
typedef  TYPE_3__ FFV1Context ;

/* Variables and functions */
 int AC_RANGE_CUSTOM_TAB ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PIX_FMT_0RGB32 ; 
 scalar_t__ AV_PIX_FMT_GBRAP10 ; 
 scalar_t__ AV_PIX_FMT_GBRAP12 ; 
 scalar_t__ AV_PIX_FMT_GBRAP16 ; 
 scalar_t__ AV_PIX_FMT_GBRP10 ; 
 scalar_t__ AV_PIX_FMT_GBRP12 ; 
 scalar_t__ AV_PIX_FMT_GBRP14 ; 
 scalar_t__ AV_PIX_FMT_GBRP16 ; 
 scalar_t__ AV_PIX_FMT_GBRP9 ; 
 scalar_t__ AV_PIX_FMT_GRAY10 ; 
 scalar_t__ AV_PIX_FMT_GRAY12 ; 
 void* AV_PIX_FMT_GRAY16 ; 
 scalar_t__ AV_PIX_FMT_GRAY8 ; 
 scalar_t__ AV_PIX_FMT_GRAY9 ; 
 scalar_t__ AV_PIX_FMT_NONE ; 
 scalar_t__ AV_PIX_FMT_RGB32 ; 
 scalar_t__ AV_PIX_FMT_YA8 ; 
 scalar_t__ AV_PIX_FMT_YUV410P ; 
 scalar_t__ AV_PIX_FMT_YUV411P ; 
 scalar_t__ AV_PIX_FMT_YUV420P ; 
 scalar_t__ AV_PIX_FMT_YUV420P10 ; 
 scalar_t__ AV_PIX_FMT_YUV420P12 ; 
 scalar_t__ AV_PIX_FMT_YUV420P14 ; 
 scalar_t__ AV_PIX_FMT_YUV420P16 ; 
 scalar_t__ AV_PIX_FMT_YUV420P9 ; 
 scalar_t__ AV_PIX_FMT_YUV422P ; 
 scalar_t__ AV_PIX_FMT_YUV422P10 ; 
 scalar_t__ AV_PIX_FMT_YUV422P12 ; 
 scalar_t__ AV_PIX_FMT_YUV422P14 ; 
 scalar_t__ AV_PIX_FMT_YUV422P16 ; 
 scalar_t__ AV_PIX_FMT_YUV422P9 ; 
 scalar_t__ AV_PIX_FMT_YUV440P ; 
 scalar_t__ AV_PIX_FMT_YUV440P10 ; 
 scalar_t__ AV_PIX_FMT_YUV440P12 ; 
 scalar_t__ AV_PIX_FMT_YUV444P ; 
 scalar_t__ AV_PIX_FMT_YUV444P10 ; 
 scalar_t__ AV_PIX_FMT_YUV444P12 ; 
 scalar_t__ AV_PIX_FMT_YUV444P14 ; 
 scalar_t__ AV_PIX_FMT_YUV444P16 ; 
 scalar_t__ AV_PIX_FMT_YUV444P9 ; 
 scalar_t__ AV_PIX_FMT_YUVA420P ; 
 scalar_t__ AV_PIX_FMT_YUVA420P10 ; 
 scalar_t__ AV_PIX_FMT_YUVA420P16 ; 
 scalar_t__ AV_PIX_FMT_YUVA420P9 ; 
 scalar_t__ AV_PIX_FMT_YUVA422P ; 
 scalar_t__ AV_PIX_FMT_YUVA422P10 ; 
 scalar_t__ AV_PIX_FMT_YUVA422P16 ; 
 scalar_t__ AV_PIX_FMT_YUVA422P9 ; 
 scalar_t__ AV_PIX_FMT_YUVA444P ; 
 scalar_t__ AV_PIX_FMT_YUVA444P10 ; 
 scalar_t__ AV_PIX_FMT_YUVA444P16 ; 
 scalar_t__ AV_PIX_FMT_YUVA444P9 ; 
 int AV_RB24 (int /*<<< orphan*/  const*) ; 
 int CONTEXT_SIZE ; 
 int /*<<< orphan*/  ENOSYS ; 
 scalar_t__ MAX_SLICES ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_8__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ff_dlog (TYPE_8__*,char*,int,int,scalar_t__) ; 
 int get_rac (TYPE_1__* const,int /*<<< orphan*/ *) ; 
 int get_symbol (TYPE_1__* const,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int read_quant_tables (TYPE_1__* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_header(FFV1Context *f)
{
    uint8_t state[CONTEXT_SIZE];
    int i, j, context_count = -1; //-1 to avoid warning
    RangeCoder *const c = &f->slice_context[0]->c;

    memset(state, 128, sizeof(state));

    if (f->version < 2) {
        int chroma_planes, chroma_h_shift, chroma_v_shift, transparency, colorspace, bits_per_raw_sample;
        unsigned v= get_symbol(c, state, 0);
        if (v >= 2) {
            av_log(f->avctx, AV_LOG_ERROR, "invalid version %d in ver01 header\n", v);
            return AVERROR_INVALIDDATA;
        }
        f->version = v;
        f->ac = get_symbol(c, state, 0);

        if (f->ac == AC_RANGE_CUSTOM_TAB) {
            for (i = 1; i < 256; i++) {
                int st = get_symbol(c, state, 1) + c->one_state[i];
                if (st < 1 || st > 255) {
                    av_log(f->avctx, AV_LOG_ERROR, "invalid state transition %d\n", st);
                    return AVERROR_INVALIDDATA;
                }
                f->state_transition[i] = st;
            }
        }

        colorspace          = get_symbol(c, state, 0); //YUV cs type
        bits_per_raw_sample = f->version > 0 ? get_symbol(c, state, 0) : f->avctx->bits_per_raw_sample;
        chroma_planes       = get_rac(c, state);
        chroma_h_shift      = get_symbol(c, state, 0);
        chroma_v_shift      = get_symbol(c, state, 0);
        transparency        = get_rac(c, state);
        if (colorspace == 0 && f->avctx->skip_alpha)
            transparency = 0;

        if (f->plane_count) {
            if (colorspace          != f->colorspace                 ||
                bits_per_raw_sample != f->avctx->bits_per_raw_sample ||
                chroma_planes       != f->chroma_planes              ||
                chroma_h_shift      != f->chroma_h_shift             ||
                chroma_v_shift      != f->chroma_v_shift             ||
                transparency        != f->transparency) {
                av_log(f->avctx, AV_LOG_ERROR, "Invalid change of global parameters\n");
                return AVERROR_INVALIDDATA;
            }
        }

        if (chroma_h_shift > 4U || chroma_v_shift > 4U) {
            av_log(f->avctx, AV_LOG_ERROR, "chroma shift parameters %d %d are invalid\n",
                   chroma_h_shift, chroma_v_shift);
            return AVERROR_INVALIDDATA;
        }

        f->colorspace                 = colorspace;
        f->avctx->bits_per_raw_sample = bits_per_raw_sample;
        f->chroma_planes              = chroma_planes;
        f->chroma_h_shift             = chroma_h_shift;
        f->chroma_v_shift             = chroma_v_shift;
        f->transparency               = transparency;

        f->plane_count    = 2 + f->transparency;
    }

    if (f->colorspace == 0) {
        if (!f->transparency && !f->chroma_planes) {
            if (f->avctx->bits_per_raw_sample <= 8)
                f->avctx->pix_fmt = AV_PIX_FMT_GRAY8;
            else if (f->avctx->bits_per_raw_sample == 9) {
                f->packed_at_lsb = 1;
                f->avctx->pix_fmt = AV_PIX_FMT_GRAY9;
            } else if (f->avctx->bits_per_raw_sample == 10) {
                f->packed_at_lsb = 1;
                f->avctx->pix_fmt = AV_PIX_FMT_GRAY10;
            } else if (f->avctx->bits_per_raw_sample == 12) {
                f->packed_at_lsb = 1;
                f->avctx->pix_fmt = AV_PIX_FMT_GRAY12;
            } else if (f->avctx->bits_per_raw_sample == 16) {
                f->packed_at_lsb = 1;
                f->avctx->pix_fmt = AV_PIX_FMT_GRAY16;
            } else if (f->avctx->bits_per_raw_sample < 16) {
                f->avctx->pix_fmt = AV_PIX_FMT_GRAY16;
            } else
                return AVERROR(ENOSYS);
        } else if (f->transparency && !f->chroma_planes) {
            if (f->avctx->bits_per_raw_sample <= 8)
                f->avctx->pix_fmt = AV_PIX_FMT_YA8;
            else
                return AVERROR(ENOSYS);
        } else if (f->avctx->bits_per_raw_sample<=8 && !f->transparency) {
            switch(16 * f->chroma_h_shift + f->chroma_v_shift) {
            case 0x00: f->avctx->pix_fmt = AV_PIX_FMT_YUV444P; break;
            case 0x01: f->avctx->pix_fmt = AV_PIX_FMT_YUV440P; break;
            case 0x10: f->avctx->pix_fmt = AV_PIX_FMT_YUV422P; break;
            case 0x11: f->avctx->pix_fmt = AV_PIX_FMT_YUV420P; break;
            case 0x20: f->avctx->pix_fmt = AV_PIX_FMT_YUV411P; break;
            case 0x22: f->avctx->pix_fmt = AV_PIX_FMT_YUV410P; break;
            }
        } else if (f->avctx->bits_per_raw_sample <= 8 && f->transparency) {
            switch(16*f->chroma_h_shift + f->chroma_v_shift) {
            case 0x00: f->avctx->pix_fmt = AV_PIX_FMT_YUVA444P; break;
            case 0x10: f->avctx->pix_fmt = AV_PIX_FMT_YUVA422P; break;
            case 0x11: f->avctx->pix_fmt = AV_PIX_FMT_YUVA420P; break;
            }
        } else if (f->avctx->bits_per_raw_sample == 9 && !f->transparency) {
            f->packed_at_lsb = 1;
            switch(16 * f->chroma_h_shift + f->chroma_v_shift) {
            case 0x00: f->avctx->pix_fmt = AV_PIX_FMT_YUV444P9; break;
            case 0x10: f->avctx->pix_fmt = AV_PIX_FMT_YUV422P9; break;
            case 0x11: f->avctx->pix_fmt = AV_PIX_FMT_YUV420P9; break;
            }
        } else if (f->avctx->bits_per_raw_sample == 9 && f->transparency) {
            f->packed_at_lsb = 1;
            switch(16 * f->chroma_h_shift + f->chroma_v_shift) {
            case 0x00: f->avctx->pix_fmt = AV_PIX_FMT_YUVA444P9; break;
            case 0x10: f->avctx->pix_fmt = AV_PIX_FMT_YUVA422P9; break;
            case 0x11: f->avctx->pix_fmt = AV_PIX_FMT_YUVA420P9; break;
            }
        } else if (f->avctx->bits_per_raw_sample == 10 && !f->transparency) {
            f->packed_at_lsb = 1;
            switch(16 * f->chroma_h_shift + f->chroma_v_shift) {
            case 0x00: f->avctx->pix_fmt = AV_PIX_FMT_YUV444P10; break;
            case 0x01: f->avctx->pix_fmt = AV_PIX_FMT_YUV440P10; break;
            case 0x10: f->avctx->pix_fmt = AV_PIX_FMT_YUV422P10; break;
            case 0x11: f->avctx->pix_fmt = AV_PIX_FMT_YUV420P10; break;
            }
        } else if (f->avctx->bits_per_raw_sample == 10 && f->transparency) {
            f->packed_at_lsb = 1;
            switch(16 * f->chroma_h_shift + f->chroma_v_shift) {
            case 0x00: f->avctx->pix_fmt = AV_PIX_FMT_YUVA444P10; break;
            case 0x10: f->avctx->pix_fmt = AV_PIX_FMT_YUVA422P10; break;
            case 0x11: f->avctx->pix_fmt = AV_PIX_FMT_YUVA420P10; break;
            }
        } else if (f->avctx->bits_per_raw_sample == 12 && !f->transparency) {
            f->packed_at_lsb = 1;
            switch(16 * f->chroma_h_shift + f->chroma_v_shift) {
            case 0x00: f->avctx->pix_fmt = AV_PIX_FMT_YUV444P12; break;
            case 0x01: f->avctx->pix_fmt = AV_PIX_FMT_YUV440P12; break;
            case 0x10: f->avctx->pix_fmt = AV_PIX_FMT_YUV422P12; break;
            case 0x11: f->avctx->pix_fmt = AV_PIX_FMT_YUV420P12; break;
            }
        } else if (f->avctx->bits_per_raw_sample == 14 && !f->transparency) {
            f->packed_at_lsb = 1;
            switch(16 * f->chroma_h_shift + f->chroma_v_shift) {
            case 0x00: f->avctx->pix_fmt = AV_PIX_FMT_YUV444P14; break;
            case 0x10: f->avctx->pix_fmt = AV_PIX_FMT_YUV422P14; break;
            case 0x11: f->avctx->pix_fmt = AV_PIX_FMT_YUV420P14; break;
            }
        } else if (f->avctx->bits_per_raw_sample == 16 && !f->transparency){
            f->packed_at_lsb = 1;
            switch(16 * f->chroma_h_shift + f->chroma_v_shift) {
            case 0x00: f->avctx->pix_fmt = AV_PIX_FMT_YUV444P16; break;
            case 0x10: f->avctx->pix_fmt = AV_PIX_FMT_YUV422P16; break;
            case 0x11: f->avctx->pix_fmt = AV_PIX_FMT_YUV420P16; break;
            }
        } else if (f->avctx->bits_per_raw_sample == 16 && f->transparency){
            f->packed_at_lsb = 1;
            switch(16 * f->chroma_h_shift + f->chroma_v_shift) {
            case 0x00: f->avctx->pix_fmt = AV_PIX_FMT_YUVA444P16; break;
            case 0x10: f->avctx->pix_fmt = AV_PIX_FMT_YUVA422P16; break;
            case 0x11: f->avctx->pix_fmt = AV_PIX_FMT_YUVA420P16; break;
            }
        }
    } else if (f->colorspace == 1) {
        if (f->chroma_h_shift || f->chroma_v_shift) {
            av_log(f->avctx, AV_LOG_ERROR,
                   "chroma subsampling not supported in this colorspace\n");
            return AVERROR(ENOSYS);
        }
        if (     f->avctx->bits_per_raw_sample <=  8 && !f->transparency)
            f->avctx->pix_fmt = AV_PIX_FMT_0RGB32;
        else if (f->avctx->bits_per_raw_sample <=  8 && f->transparency)
            f->avctx->pix_fmt = AV_PIX_FMT_RGB32;
        else if (f->avctx->bits_per_raw_sample ==  9 && !f->transparency)
            f->avctx->pix_fmt = AV_PIX_FMT_GBRP9;
        else if (f->avctx->bits_per_raw_sample == 10 && !f->transparency)
            f->avctx->pix_fmt = AV_PIX_FMT_GBRP10;
        else if (f->avctx->bits_per_raw_sample == 10 && f->transparency)
            f->avctx->pix_fmt = AV_PIX_FMT_GBRAP10;
        else if (f->avctx->bits_per_raw_sample == 12 && !f->transparency)
            f->avctx->pix_fmt = AV_PIX_FMT_GBRP12;
        else if (f->avctx->bits_per_raw_sample == 12 && f->transparency)
            f->avctx->pix_fmt = AV_PIX_FMT_GBRAP12;
        else if (f->avctx->bits_per_raw_sample == 14 && !f->transparency)
            f->avctx->pix_fmt = AV_PIX_FMT_GBRP14;
        else if (f->avctx->bits_per_raw_sample == 16 && !f->transparency) {
            f->avctx->pix_fmt = AV_PIX_FMT_GBRP16;
            f->use32bit = 1;
        }
        else if (f->avctx->bits_per_raw_sample == 16 && f->transparency) {
            f->avctx->pix_fmt = AV_PIX_FMT_GBRAP16;
            f->use32bit = 1;
        }
    } else {
        av_log(f->avctx, AV_LOG_ERROR, "colorspace not supported\n");
        return AVERROR(ENOSYS);
    }
    if (f->avctx->pix_fmt == AV_PIX_FMT_NONE) {
        av_log(f->avctx, AV_LOG_ERROR, "format not supported\n");
        return AVERROR(ENOSYS);
    }

    ff_dlog(f->avctx, "%d %d %d\n",
            f->chroma_h_shift, f->chroma_v_shift, f->avctx->pix_fmt);
    if (f->version < 2) {
        context_count = read_quant_tables(c, f->quant_table);
        if (context_count < 0) {
            av_log(f->avctx, AV_LOG_ERROR, "read_quant_table error\n");
            return AVERROR_INVALIDDATA;
        }
        f->slice_count = f->max_slice_count;
    } else if (f->version < 3) {
        f->slice_count = get_symbol(c, state, 0);
    } else {
        const uint8_t *p = c->bytestream_end;
        for (f->slice_count = 0;
             f->slice_count < MAX_SLICES && 3 + 5*!!f->ec < p - c->bytestream_start;
             f->slice_count++) {
            int trailer = 3 + 5*!!f->ec;
            int size = AV_RB24(p-trailer);
            if (size + trailer > p - c->bytestream_start)
                break;
            p -= size + trailer;
        }
    }
    if (f->slice_count > (unsigned)MAX_SLICES || f->slice_count <= 0 || f->slice_count > f->max_slice_count) {
        av_log(f->avctx, AV_LOG_ERROR, "slice count %d is invalid (max=%d)\n", f->slice_count, f->max_slice_count);
        return AVERROR_INVALIDDATA;
    }

    for (j = 0; j < f->slice_count; j++) {
        FFV1Context *fs = f->slice_context[j];
        fs->ac            = f->ac;
        fs->packed_at_lsb = f->packed_at_lsb;

        fs->slice_damaged = 0;

        if (f->version == 2) {
            fs->slice_x      =  get_symbol(c, state, 0)      * f->width ;
            fs->slice_y      =  get_symbol(c, state, 0)      * f->height;
            fs->slice_width  = (get_symbol(c, state, 0) + 1) * f->width  + fs->slice_x;
            fs->slice_height = (get_symbol(c, state, 0) + 1) * f->height + fs->slice_y;

            fs->slice_x     /= f->num_h_slices;
            fs->slice_y     /= f->num_v_slices;
            fs->slice_width  = fs->slice_width  / f->num_h_slices - fs->slice_x;
            fs->slice_height = fs->slice_height / f->num_v_slices - fs->slice_y;
            if ((unsigned)fs->slice_width  > f->width ||
                (unsigned)fs->slice_height > f->height)
                return AVERROR_INVALIDDATA;
            if (   (unsigned)fs->slice_x + (uint64_t)fs->slice_width  > f->width
                || (unsigned)fs->slice_y + (uint64_t)fs->slice_height > f->height)
                return AVERROR_INVALIDDATA;
        }

        for (i = 0; i < f->plane_count; i++) {
            PlaneContext *const p = &fs->plane[i];

            if (f->version == 2) {
                int idx = get_symbol(c, state, 0);
                if (idx > (unsigned)f->quant_table_count) {
                    av_log(f->avctx, AV_LOG_ERROR,
                           "quant_table_index out of range\n");
                    return AVERROR_INVALIDDATA;
                }
                p->quant_table_index = idx;
                memcpy(p->quant_table, f->quant_tables[idx],
                       sizeof(p->quant_table));
                context_count = f->context_count[idx];
            } else {
                memcpy(p->quant_table, f->quant_table, sizeof(p->quant_table));
            }

            if (f->version <= 2) {
                av_assert0(context_count >= 0);
                if (p->context_count < context_count) {
                    av_freep(&p->state);
                    av_freep(&p->vlc_state);
                }
                p->context_count = context_count;
            }
        }
    }
    return 0;
}