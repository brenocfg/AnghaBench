#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/  properties; TYPE_2__* priv_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  top_field_first; } ;
struct TYPE_6__ {char* a53_caption; int a53_caption_size; TYPE_1__ mpeg_enc_ctx; } ;
typedef  TYPE_2__ Mpeg1Context ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  FF_CODEC_PROPERTY_CLOSED_CAPTIONS ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 void* av_malloc (int) ; 
 char* av_mallocz (int) ; 
 char* ff_reverse ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mpeg_decode_a53_cc(AVCodecContext *avctx,
                              const uint8_t *p, int buf_size)
{
    Mpeg1Context *s1 = avctx->priv_data;

    if (buf_size >= 6 &&
        p[0] == 'G' && p[1] == 'A' && p[2] == '9' && p[3] == '4' &&
        p[4] == 3 && (p[5] & 0x40)) {
        /* extract A53 Part 4 CC data */
        int cc_count = p[5] & 0x1f;
        if (cc_count > 0 && buf_size >= 7 + cc_count * 3) {
            av_freep(&s1->a53_caption);
            s1->a53_caption_size = cc_count * 3;
            s1->a53_caption      = av_malloc(s1->a53_caption_size);
            if (!s1->a53_caption) {
                s1->a53_caption_size = 0;
            } else {
                memcpy(s1->a53_caption, p + 7, s1->a53_caption_size);
            }
            avctx->properties |= FF_CODEC_PROPERTY_CLOSED_CAPTIONS;
        }
        return 1;
    } else if (buf_size >= 2 &&
               p[0] == 0x03 && (p[1]&0x7f) == 0x01) {
        /* extract SCTE-20 CC data */
        GetBitContext gb;
        int cc_count = 0;
        int i;

        init_get_bits(&gb, p + 2, buf_size - 2);
        cc_count = get_bits(&gb, 5);
        if (cc_count > 0) {
            av_freep(&s1->a53_caption);
            s1->a53_caption_size = cc_count * 3;
            s1->a53_caption      = av_mallocz(s1->a53_caption_size);
            if (!s1->a53_caption) {
                s1->a53_caption_size = 0;
            } else {
                uint8_t field, cc1, cc2;
                uint8_t *cap = s1->a53_caption;
                for (i = 0; i < cc_count && get_bits_left(&gb) >= 26; i++) {
                    skip_bits(&gb, 2); // priority
                    field = get_bits(&gb, 2);
                    skip_bits(&gb, 5); // line_offset
                    cc1 = get_bits(&gb, 8);
                    cc2 = get_bits(&gb, 8);
                    skip_bits(&gb, 1); // marker

                    if (!field) { // forbidden
                        cap[0] = cap[1] = cap[2] = 0x00;
                    } else {
                        field = (field == 2 ? 1 : 0);
                        if (!s1->mpeg_enc_ctx.top_field_first) field = !field;
                        cap[0] = 0x04 | field;
                        cap[1] = ff_reverse[cc1];
                        cap[2] = ff_reverse[cc2];
                    }
                    cap += 3;
                }
            }
            avctx->properties |= FF_CODEC_PROPERTY_CLOSED_CAPTIONS;
        }
        return 1;
    } else if (buf_size >= 11 &&
               p[0] == 'C' && p[1] == 'C' && p[2] == 0x01 && p[3] == 0xf8) {
        /* extract DVD CC data
         *
         * uint32_t   user_data_start_code        0x000001B2    (big endian)
         * uint16_t   user_identifier             0x4343 "CC"
         * uint8_t    user_data_type_code         0x01
         * uint8_t    caption_block_size          0xF8
         * uint8_t
         *   bit 7    caption_odd_field_first     1=odd field (CC1/CC2) first  0=even field (CC3/CC4) first
         *   bit 6    caption_filler              0
         *   bit 5:1  caption_block_count         number of caption blocks (pairs of caption words = frames). Most DVDs use 15 per start of GOP.
         *   bit 0    caption_extra_field_added   1=one additional caption word
         *
         * struct caption_field_block {
         *   uint8_t
         *     bit 7:1 caption_filler             0x7F (all 1s)
         *     bit 0   caption_field_odd          1=odd field (this is CC1/CC2)  0=even field (this is CC3/CC4)
         *   uint8_t   caption_first_byte
         *   uint8_t   caption_second_byte
         * } caption_block[(caption_block_count * 2) + caption_extra_field_added];
         *
         * Some DVDs encode caption data for both fields with caption_field_odd=1. The only way to decode the fields
         * correctly is to start on the field indicated by caption_odd_field_first and count between odd/even fields.
         * Don't assume that the first caption word is the odd field. There do exist MPEG files in the wild that start
         * on the even field. There also exist DVDs in the wild that encode an odd field count and the
         * caption_extra_field_added/caption_odd_field_first bits change per packet to allow that. */
        int cc_count = 0;
        int i;
        // There is a caption count field in the data, but it is often
        // incorrect.  So count the number of captions present.
        for (i = 5; i + 6 <= buf_size && ((p[i] & 0xfe) == 0xfe); i += 6)
            cc_count++;
        // Transform the DVD format into A53 Part 4 format
        if (cc_count > 0) {
            av_freep(&s1->a53_caption);
            s1->a53_caption_size = cc_count * 6;
            s1->a53_caption      = av_malloc(s1->a53_caption_size);
            if (!s1->a53_caption) {
                s1->a53_caption_size = 0;
            } else {
                uint8_t field1 = !!(p[4] & 0x80);
                uint8_t *cap = s1->a53_caption;
                p += 5;
                for (i = 0; i < cc_count; i++) {
                    cap[0] = (p[0] == 0xff && field1) ? 0xfc : 0xfd;
                    cap[1] = p[1];
                    cap[2] = p[2];
                    cap[3] = (p[3] == 0xff && !field1) ? 0xfc : 0xfd;
                    cap[4] = p[4];
                    cap[5] = p[5];
                    cap += 6;
                    p += 6;
                }
            }
            avctx->properties |= FF_CODEC_PROPERTY_CLOSED_CAPTIONS;
        }
        return 1;
    }
    return 0;
}