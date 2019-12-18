#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int channels; int profile; int samplerate_index; scalar_t__ needs_pce; } ;
struct TYPE_5__ {int extradata_size; int /*<<< orphan*/  extradata; TYPE_2__* priv_data; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ AVCodecContext ;
typedef  TYPE_2__ AACEncContext ;

/* Variables and functions */
 int AOT_SBR ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_mallocz (int const) ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int put_bits_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_pce (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int put_audio_specific_config(AVCodecContext *avctx)
{
    PutBitContext pb;
    AACEncContext *s = avctx->priv_data;
    int channels = (!s->needs_pce)*(s->channels - (s->channels == 8 ? 1 : 0));
    const int max_size = 32;

    avctx->extradata = av_mallocz(max_size);
    if (!avctx->extradata)
        return AVERROR(ENOMEM);

    init_put_bits(&pb, avctx->extradata, max_size);
    put_bits(&pb, 5, s->profile+1); //profile
    put_bits(&pb, 4, s->samplerate_index); //sample rate index
    put_bits(&pb, 4, channels);
    //GASpecificConfig
    put_bits(&pb, 1, 0); //frame length - 1024 samples
    put_bits(&pb, 1, 0); //does not depend on core coder
    put_bits(&pb, 1, 0); //is not extension
    if (s->needs_pce)
        put_pce(&pb, avctx);

    //Explicitly Mark SBR absent
    put_bits(&pb, 11, 0x2b7); //sync extension
    put_bits(&pb, 5,  AOT_SBR);
    put_bits(&pb, 1,  0);
    flush_put_bits(&pb);
    avctx->extradata_size = put_bits_count(&pb) >> 3;

    return 0;
}