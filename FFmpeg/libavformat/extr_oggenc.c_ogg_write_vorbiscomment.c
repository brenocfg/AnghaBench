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
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  int /*<<< orphan*/  AVChapter ;

/* Variables and functions */
 int INT_MAX ; 
 char* LIBAVFORMAT_IDENT ; 
 int /*<<< orphan*/ * av_mallocz (int) ; 
 int /*<<< orphan*/  bytestream_put_byte (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  ff_metadata_conv (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ff_vorbiscomment_length (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **,unsigned int) ; 
 int /*<<< orphan*/  ff_vorbiscomment_metadata_conv ; 
 int /*<<< orphan*/  ff_vorbiscomment_write (int /*<<< orphan*/ **,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ **,unsigned int) ; 

__attribute__((used)) static uint8_t *ogg_write_vorbiscomment(int64_t offset, int bitexact,
                                        int *header_len, AVDictionary **m, int framing_bit,
                                        AVChapter **chapters, unsigned int nb_chapters)
{
    const char *vendor = bitexact ? "ffmpeg" : LIBAVFORMAT_IDENT;
    int64_t size;
    uint8_t *p, *p0;

    ff_metadata_conv(m, ff_vorbiscomment_metadata_conv, NULL);

    size = offset + ff_vorbiscomment_length(*m, vendor, chapters, nb_chapters) + framing_bit;
    if (size > INT_MAX)
        return NULL;
    p = av_mallocz(size);
    if (!p)
        return NULL;
    p0 = p;

    p += offset;
    ff_vorbiscomment_write(&p, m, vendor, chapters, nb_chapters);
    if (framing_bit)
        bytestream_put_byte(&p, 1);

    *header_len = size;
    return p0;
}