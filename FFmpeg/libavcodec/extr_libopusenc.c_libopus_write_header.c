#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct TYPE_3__ {char* extradata; int channels; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  initial_padding; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  bytestream_put_buffer (char**,char const*,int) ; 
 int /*<<< orphan*/  bytestream_put_byte (char**,int) ; 
 int /*<<< orphan*/  bytestream_put_le16 (char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream_put_le32 (char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void libopus_write_header(AVCodecContext *avctx, int stream_count,
                                 int coupled_stream_count,
                                 int mapping_family,
                                 const uint8_t *channel_mapping)
{
    uint8_t *p   = avctx->extradata;
    int channels = avctx->channels;

    bytestream_put_buffer(&p, "OpusHead", 8);
    bytestream_put_byte(&p, 1); /* Version */
    bytestream_put_byte(&p, channels);
    bytestream_put_le16(&p, avctx->initial_padding); /* Lookahead samples at 48kHz */
    bytestream_put_le32(&p, avctx->sample_rate); /* Original sample rate */
    bytestream_put_le16(&p, 0); /* Gain of 0dB is recommended. */

    /* Channel mapping */
    bytestream_put_byte(&p, mapping_family);
    if (mapping_family != 0) {
        bytestream_put_byte(&p, stream_count);
        bytestream_put_byte(&p, coupled_stream_count);
        bytestream_put_buffer(&p, channel_mapping, channels);
    }
}