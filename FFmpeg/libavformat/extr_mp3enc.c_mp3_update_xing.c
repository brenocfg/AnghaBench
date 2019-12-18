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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_8__ {int /*<<< orphan*/  pb; int /*<<< orphan*/ * streams; TYPE_1__* priv_data; } ;
struct TYPE_7__ {scalar_t__ track_gain; scalar_t__ album_gain; int /*<<< orphan*/  track_peak; } ;
struct TYPE_6__ {int xing_offset; long long frames; long long size; int pos; long long* bag; int delay; int padding; long long audio_size; int audio_crc; int /*<<< orphan*/  xing_frame_size; scalar_t__* xing_frame; int /*<<< orphan*/  xing_frame_offset; int /*<<< orphan*/  has_variable_bitrate; } ;
typedef  TYPE_1__ MP3Context ;
typedef  TYPE_2__ AVReplayGain ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CRC_16_ANSI_LE ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_PKT_DATA_REPLAYGAIN ; 
 int /*<<< orphan*/  AV_WB16 (scalar_t__*,int) ; 
 int /*<<< orphan*/  AV_WB24 (scalar_t__*,int) ; 
 int /*<<< orphan*/  AV_WB32 (scalar_t__*,long long) ; 
 int /*<<< orphan*/  AV_WL32 (scalar_t__*,int /*<<< orphan*/ ) ; 
 int FFABS (int) ; 
 scalar_t__ FFMIN (int,int) ; 
 scalar_t__ INT32_MIN ; 
 int /*<<< orphan*/  MKTAG (char,char,float,char) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int XING_SIZE ; 
 int XING_TOC_SIZE ; 
 int av_crc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  av_crc_get_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 long long av_rescale (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ av_stream_get_side_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mp3_update_xing(AVFormatContext *s)
{
    MP3Context  *mp3 = s->priv_data;
    AVReplayGain *rg;
    uint16_t tag_crc;
    uint8_t *toc;
    int i, rg_size;
    int64_t old_pos = avio_tell(s->pb);

    /* replace "Xing" identification string with "Info" for CBR files. */
    if (!mp3->has_variable_bitrate)
        AV_WL32(mp3->xing_frame + mp3->xing_offset, MKTAG('I', 'n', 'f', 'o'));

    AV_WB32(mp3->xing_frame + mp3->xing_offset + 8,  mp3->frames);
    AV_WB32(mp3->xing_frame + mp3->xing_offset + 12, mp3->size);

    toc    = mp3->xing_frame + mp3->xing_offset + 16;
    toc[0] = 0;  // first toc entry has to be zero.
    for (i = 1; i < XING_TOC_SIZE; ++i) {
        int j = i * mp3->pos / XING_TOC_SIZE;
        int seek_point = 256LL * mp3->bag[j] / mp3->size;
        toc[i] = FFMIN(seek_point, 255);
    }

    /* write replaygain */
    rg = (AVReplayGain*)av_stream_get_side_data(s->streams[0], AV_PKT_DATA_REPLAYGAIN,
                                                &rg_size);
    if (rg && rg_size >= sizeof(*rg)) {
        uint16_t val;

        AV_WB32(mp3->xing_frame + mp3->xing_offset + 131,
                av_rescale(rg->track_peak, 1 << 23, 100000));

        if (rg->track_gain != INT32_MIN) {
            val  = FFABS(rg->track_gain / 10000) & ((1 << 9) - 1);
            val |= (rg->track_gain < 0) << 9;
            val |= 1 << 13;
            AV_WB16(mp3->xing_frame + mp3->xing_offset + 135, val);
        }

        if (rg->album_gain != INT32_MIN) {
            val  = FFABS(rg->album_gain / 10000) & ((1 << 9) - 1);
            val |= (rg->album_gain < 0) << 9;
            val |= 1 << 14;
            AV_WB16(mp3->xing_frame + mp3->xing_offset + 137, val);
        }
    }

    /* write encoder delay/padding */
    if (mp3->delay >= 1 << 12) {
        mp3->delay = (1 << 12) - 1;
        av_log(s, AV_LOG_WARNING, "Too many samples of initial padding.\n");
    }
    if (mp3->padding >= 1 << 12) {
        mp3->padding = (1 << 12) - 1;
        av_log(s, AV_LOG_WARNING, "Too many samples of trailing padding.\n");
    }
    AV_WB24(mp3->xing_frame + mp3->xing_offset + 141, (mp3->delay << 12) + mp3->padding);

    AV_WB32(mp3->xing_frame + mp3->xing_offset + XING_SIZE - 8, mp3->audio_size);
    AV_WB16(mp3->xing_frame + mp3->xing_offset + XING_SIZE - 4, mp3->audio_crc);

    tag_crc = av_crc(av_crc_get_table(AV_CRC_16_ANSI_LE), 0, mp3->xing_frame, 190);
    AV_WB16(mp3->xing_frame + mp3->xing_offset + XING_SIZE - 2, tag_crc);

    avio_seek(s->pb,  mp3->xing_frame_offset, SEEK_SET);
    avio_write(s->pb, mp3->xing_frame, mp3->xing_frame_size);
    avio_seek(s->pb, old_pos, SEEK_SET);
}