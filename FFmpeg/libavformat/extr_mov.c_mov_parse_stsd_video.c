#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  codec_name ;
struct TYPE_8__ {TYPE_1__* codecpar; int /*<<< orphan*/  metadata; } ;
struct TYPE_7__ {int has_palette; int /*<<< orphan*/  palette; } ;
struct TYPE_6__ {int width; int height; scalar_t__ codec_tag; int bits_per_coded_sample; int /*<<< orphan*/  codec_id; } ;
typedef  TYPE_2__ MOVStreamContext ;
typedef  int /*<<< orphan*/  MOVContext ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CODEC_ID_FLV1 ; 
 scalar_t__ MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,scalar_t__*,int /*<<< orphan*/ ) ; 
 unsigned int avio_r8 (int /*<<< orphan*/ *) ; 
 void* avio_rb16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ *) ; 
 scalar_t__ ff_get_qtpalette (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mov_read_mac_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,scalar_t__*,int) ; 
 int /*<<< orphan*/  strncmp (scalar_t__*,char*,int) ; 

__attribute__((used)) static void mov_parse_stsd_video(MOVContext *c, AVIOContext *pb,
                                 AVStream *st, MOVStreamContext *sc)
{
    uint8_t codec_name[32] = { 0 };
    int64_t stsd_start;
    unsigned int len;

    /* The first 16 bytes of the video sample description are already
     * read in ff_mov_read_stsd_entries() */
    stsd_start = avio_tell(pb) - 16;

    avio_rb16(pb); /* version */
    avio_rb16(pb); /* revision level */
    avio_rb32(pb); /* vendor */
    avio_rb32(pb); /* temporal quality */
    avio_rb32(pb); /* spatial quality */

    st->codecpar->width  = avio_rb16(pb); /* width */
    st->codecpar->height = avio_rb16(pb); /* height */

    avio_rb32(pb); /* horiz resolution */
    avio_rb32(pb); /* vert resolution */
    avio_rb32(pb); /* data size, always 0 */
    avio_rb16(pb); /* frames per samples */

    len = avio_r8(pb); /* codec name, pascal string */
    if (len > 31)
        len = 31;
    mov_read_mac_string(c, pb, len, codec_name, sizeof(codec_name));
    if (len < 31)
        avio_skip(pb, 31 - len);

    if (codec_name[0])
        av_dict_set(&st->metadata, "encoder", codec_name, 0);

    /* codec_tag YV12 triggers an UV swap in rawdec.c */
    if (!strncmp(codec_name, "Planar Y'CbCr 8-bit 4:2:0", 25)) {
        st->codecpar->codec_tag = MKTAG('I', '4', '2', '0');
        st->codecpar->width &= ~1;
        st->codecpar->height &= ~1;
    }
    /* Flash Media Server uses tag H.263 with Sorenson Spark */
    if (st->codecpar->codec_tag == MKTAG('H','2','6','3') &&
        !strncmp(codec_name, "Sorenson H263", 13))
        st->codecpar->codec_id = AV_CODEC_ID_FLV1;

    st->codecpar->bits_per_coded_sample = avio_rb16(pb); /* depth */

    avio_seek(pb, stsd_start, SEEK_SET);

    if (ff_get_qtpalette(st->codecpar->codec_id, pb, sc->palette)) {
        st->codecpar->bits_per_coded_sample &= 0x1F;
        sc->has_palette = 1;
    }
}