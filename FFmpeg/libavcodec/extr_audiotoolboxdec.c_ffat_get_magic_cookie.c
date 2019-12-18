#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  scalar_t__ UInt32 ;
struct TYPE_5__ {char* extradata; scalar_t__ extradata_size; } ;
struct TYPE_4__ {scalar_t__ codec_id; TYPE_2__* priv_data; } ;
typedef  int /*<<< orphan*/  PutByteContext ;
typedef  TYPE_1__ AVCodecContext ;
typedef  TYPE_2__ ATDecodeContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_AAC ; 
 char* av_malloc (scalar_t__) ; 
 int /*<<< orphan*/  bytestream2_init_writer (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  bytestream2_put_be16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream2_put_be24 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream2_put_be32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream2_put_buffer (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  bytestream2_put_byte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_descr (int /*<<< orphan*/ *,int,scalar_t__) ; 

__attribute__((used)) static uint8_t* ffat_get_magic_cookie(AVCodecContext *avctx, UInt32 *cookie_size)
{
    ATDecodeContext *at = avctx->priv_data;
    if (avctx->codec_id == AV_CODEC_ID_AAC) {
        char *extradata;
        PutByteContext pb;
        *cookie_size = 5 + 3 + 5+13 + 5+at->extradata_size;
        if (!(extradata = av_malloc(*cookie_size)))
            return NULL;

        bytestream2_init_writer(&pb, extradata, *cookie_size);

        // ES descriptor
        put_descr(&pb, 0x03, 3 + 5+13 + 5+at->extradata_size);
        bytestream2_put_be16(&pb, 0);
        bytestream2_put_byte(&pb, 0x00); // flags (= no flags)

        // DecoderConfig descriptor
        put_descr(&pb, 0x04, 13 + 5+at->extradata_size);

        // Object type indication
        bytestream2_put_byte(&pb, 0x40);

        bytestream2_put_byte(&pb, 0x15); // flags (= Audiostream)

        bytestream2_put_be24(&pb, 0); // Buffersize DB

        bytestream2_put_be32(&pb, 0); // maxbitrate
        bytestream2_put_be32(&pb, 0); // avgbitrate

        // DecoderSpecific info descriptor
        put_descr(&pb, 0x05, at->extradata_size);
        bytestream2_put_buffer(&pb, at->extradata, at->extradata_size);
        return extradata;
    } else {
        *cookie_size = at->extradata_size;
        return at->extradata;
    }
}