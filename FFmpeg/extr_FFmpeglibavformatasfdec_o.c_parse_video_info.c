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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {TYPE_1__* codecpar; } ;
struct TYPE_5__ {unsigned int codec_tag; scalar_t__ extradata_size; scalar_t__ extradata; int /*<<< orphan*/  codec_id; void* height; void* width; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 scalar_t__ BMP_HEADER_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ FFMAX (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ av_malloc (scalar_t__) ; 
 int avio_read (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  avio_rl16 (int /*<<< orphan*/ *) ; 
 void* avio_rl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_codec_bmp_tags ; 
 int /*<<< orphan*/  ff_codec_get_id (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int ff_get_bmp_header (int /*<<< orphan*/ *,TYPE_2__*,scalar_t__*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int parse_video_info(AVIOContext *pb, AVStream *st)
{
    uint16_t size_asf; // ASF-specific Format Data size
    uint32_t size_bmp; // BMP_HEADER-specific Format Data size
    unsigned int tag;

    st->codecpar->width  = avio_rl32(pb);
    st->codecpar->height = avio_rl32(pb);
    avio_skip(pb, 1); // skip reserved flags
    size_asf = avio_rl16(pb);
    tag = ff_get_bmp_header(pb, st, &size_bmp);
    st->codecpar->codec_tag = tag;
    st->codecpar->codec_id  = ff_codec_get_id(ff_codec_bmp_tags, tag);
    size_bmp = FFMAX(size_asf, size_bmp);

    if (size_bmp > BMP_HEADER_SIZE &&
        size_bmp < INT_MAX - AV_INPUT_BUFFER_PADDING_SIZE) {
        int ret;
        st->codecpar->extradata_size  = size_bmp - BMP_HEADER_SIZE;
        if (!(st->codecpar->extradata = av_malloc(st->codecpar->extradata_size +
                                               AV_INPUT_BUFFER_PADDING_SIZE))) {
            st->codecpar->extradata_size = 0;
            return AVERROR(ENOMEM);
        }
        memset(st->codecpar->extradata + st->codecpar->extradata_size , 0,
               AV_INPUT_BUFFER_PADDING_SIZE);
        if ((ret = avio_read(pb, st->codecpar->extradata,
                             st->codecpar->extradata_size)) < 0)
            return ret;
    }
    return 0;
}