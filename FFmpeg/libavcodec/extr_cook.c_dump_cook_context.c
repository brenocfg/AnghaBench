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
struct TYPE_7__ {int channels; int sample_rate; scalar_t__ bit_rate; } ;
struct TYPE_6__ {TYPE_1__* subpacket; TYPE_3__* avctx; } ;
struct TYPE_5__ {scalar_t__ cookversion; int js_subband_start; int js_vlc_bits; int samples_per_channel; int subbands; int log2_numvector_size; int numvector_size; int total_subbands; } ;
typedef  TYPE_2__ COOKContext ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT (char*,int) ; 
 scalar_t__ STEREO ; 
 int /*<<< orphan*/  ff_dlog (TYPE_3__*,char*,...) ; 

__attribute__((used)) static void dump_cook_context(COOKContext *q)
{
    //int i=0;
#define PRINT(a, b) ff_dlog(q->avctx, " %s = %d\n", a, b);
    ff_dlog(q->avctx, "COOKextradata\n");
    ff_dlog(q->avctx, "cookversion=%x\n", q->subpacket[0].cookversion);
    if (q->subpacket[0].cookversion > STEREO) {
        PRINT("js_subband_start", q->subpacket[0].js_subband_start);
        PRINT("js_vlc_bits", q->subpacket[0].js_vlc_bits);
    }
    ff_dlog(q->avctx, "COOKContext\n");
    PRINT("nb_channels", q->avctx->channels);
    PRINT("bit_rate", (int)q->avctx->bit_rate);
    PRINT("sample_rate", q->avctx->sample_rate);
    PRINT("samples_per_channel", q->subpacket[0].samples_per_channel);
    PRINT("subbands", q->subpacket[0].subbands);
    PRINT("js_subband_start", q->subpacket[0].js_subband_start);
    PRINT("log2_numvector_size", q->subpacket[0].log2_numvector_size);
    PRINT("numvector_size", q->subpacket[0].numvector_size);
    PRINT("total_subbands", q->subpacket[0].total_subbands);
}