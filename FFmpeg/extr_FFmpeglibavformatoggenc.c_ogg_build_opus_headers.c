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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int extradata_size; char* extradata; } ;
struct TYPE_5__ {int* header_len; int /*<<< orphan*/ ** header; } ;
typedef  TYPE_1__ OGGStreamContext ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  TYPE_2__ AVCodecParameters ;
typedef  int /*<<< orphan*/  AVChapter ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  ENOMEM ; 
 int OPUS_HEADER_SIZE ; 
 int /*<<< orphan*/ * av_mallocz (int) ; 
 int /*<<< orphan*/  bytestream_put_buffer (int /*<<< orphan*/ **,char*,int) ; 
 int /*<<< orphan*/ * ogg_write_vorbiscomment (int,int,int*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ **,unsigned int) ; 

__attribute__((used)) static int ogg_build_opus_headers(AVCodecParameters *par,
                                  OGGStreamContext *oggstream, int bitexact,
                                  AVDictionary **m, AVChapter **chapters,
                                  unsigned int nb_chapters)
{
    uint8_t *p;

    if (par->extradata_size < OPUS_HEADER_SIZE)
        return AVERROR_INVALIDDATA;

    /* first packet: Opus header */
    p = av_mallocz(par->extradata_size);
    if (!p)
        return AVERROR(ENOMEM);
    oggstream->header[0] = p;
    oggstream->header_len[0] = par->extradata_size;
    bytestream_put_buffer(&p, par->extradata, par->extradata_size);

    /* second packet: VorbisComment */
    p = ogg_write_vorbiscomment(8, bitexact, &oggstream->header_len[1], m, 0, chapters, nb_chapters);
    if (!p)
        return AVERROR(ENOMEM);
    oggstream->header[1] = p;
    bytestream_put_buffer(&p, "OpusTags", 8);

    return 0;
}