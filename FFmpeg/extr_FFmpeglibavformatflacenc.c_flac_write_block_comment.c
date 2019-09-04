#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 char* LIBAVFORMAT_IDENT ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * av_malloc (int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bytestream_put_be24 (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  bytestream_put_byte (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  ff_metadata_conv (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ff_vorbiscomment_length (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_vorbiscomment_metadata_conv ; 
 int /*<<< orphan*/  ff_vorbiscomment_write (int /*<<< orphan*/ **,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int flac_write_block_comment(AVIOContext *pb, AVDictionary **m,
                                    int last_block, int bitexact)
{
    const char *vendor = bitexact ? "ffmpeg" : LIBAVFORMAT_IDENT;
    int64_t len;
    uint8_t *p, *p0;

    ff_metadata_conv(m, ff_vorbiscomment_metadata_conv, NULL);

    len = ff_vorbiscomment_length(*m, vendor, NULL, 0);
    if (len >= ((1<<24) - 4))
        return AVERROR(EINVAL);
    p0 = av_malloc(len+4);
    if (!p0)
        return AVERROR(ENOMEM);
    p = p0;

    bytestream_put_byte(&p, last_block ? 0x84 : 0x04);
    bytestream_put_be24(&p, len);
    ff_vorbiscomment_write(&p, m, vendor, NULL, 0);

    avio_write(pb, p0, len+4);
    av_freep(&p0);
    p = NULL;

    return 0;
}