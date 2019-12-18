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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int channels; int initial_padding; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/ * extradata; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  bytestream_put_buffer (int /*<<< orphan*/ **,char*,int) ; 
 int /*<<< orphan*/  bytestream_put_byte (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  bytestream_put_le16 (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  bytestream_put_le32 (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void opus_write_extradata(AVCodecContext *avctx)
{
    uint8_t *bs = avctx->extradata;

    bytestream_put_buffer(&bs, "OpusHead", 8);
    bytestream_put_byte  (&bs, 0x1);
    bytestream_put_byte  (&bs, avctx->channels);
    bytestream_put_le16  (&bs, avctx->initial_padding);
    bytestream_put_le32  (&bs, avctx->sample_rate);
    bytestream_put_le16  (&bs, 0x0);
    bytestream_put_byte  (&bs, 0x0); /* Default layout */
}