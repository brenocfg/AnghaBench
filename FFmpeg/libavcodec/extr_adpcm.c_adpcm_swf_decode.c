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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ int8_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_7__ {TYPE_1__* status; } ;
struct TYPE_6__ {int channels; TYPE_3__* priv_data; } ;
struct TYPE_5__ {int predictor; int step_index; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ AVCodecContext ;
typedef  TYPE_3__ ADPCMDecodeContext ;

/* Variables and functions */
 size_t av_clip (size_t,int /*<<< orphan*/ ,int) ; 
 int av_clip_int16 (int) ; 
 int* ff_adpcm_step_table ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int get_sbits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 scalar_t__** swf_index_tables ; 

__attribute__((used)) static void adpcm_swf_decode(AVCodecContext *avctx, const uint8_t *buf, int buf_size, int16_t *samples)
{
    ADPCMDecodeContext *c = avctx->priv_data;
    GetBitContext gb;
    const int8_t *table;
    int k0, signmask, nb_bits, count;
    int size = buf_size*8;
    int i;

    init_get_bits(&gb, buf, size);

    //read bits & initial values
    nb_bits = get_bits(&gb, 2)+2;
    table = swf_index_tables[nb_bits-2];
    k0 = 1 << (nb_bits-2);
    signmask = 1 << (nb_bits-1);

    while (get_bits_count(&gb) <= size - 22*avctx->channels) {
        for (i = 0; i < avctx->channels; i++) {
            *samples++ = c->status[i].predictor = get_sbits(&gb, 16);
            c->status[i].step_index = get_bits(&gb, 6);
        }

        for (count = 0; get_bits_count(&gb) <= size - nb_bits*avctx->channels && count < 4095; count++) {
            int i;

            for (i = 0; i < avctx->channels; i++) {
                // similar to IMA adpcm
                int delta = get_bits(&gb, nb_bits);
                int step = ff_adpcm_step_table[c->status[i].step_index];
                int vpdiff = 0; // vpdiff = (delta+0.5)*step/4
                int k = k0;

                do {
                    if (delta & k)
                        vpdiff += step;
                    step >>= 1;
                    k >>= 1;
                } while(k);
                vpdiff += step;

                if (delta & signmask)
                    c->status[i].predictor -= vpdiff;
                else
                    c->status[i].predictor += vpdiff;

                c->status[i].step_index += table[delta & (~signmask)];

                c->status[i].step_index = av_clip(c->status[i].step_index, 0, 88);
                c->status[i].predictor = av_clip_int16(c->status[i].predictor);

                *samples++ = c->status[i].predictor;
            }
        }
    }
}