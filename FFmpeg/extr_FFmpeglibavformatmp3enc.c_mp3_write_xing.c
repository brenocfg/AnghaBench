#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  int uint16_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  encoder_str ;
struct TYPE_28__ {int const sample_rate; int channels; int bit_rate; } ;
struct TYPE_27__ {char* value; } ;
struct TYPE_26__ {TYPE_4__* pb; TYPE_1__** streams; TYPE_3__* priv_data; } ;
struct TYPE_25__ {int seekable; } ;
struct TYPE_24__ {size_t audio_stream_idx; int xing_offset; int size; int want; int xing_frame_size; char* xing_frame; int audio_size; int /*<<< orphan*/  xing_frame_offset; scalar_t__ pos; scalar_t__ seen; int /*<<< orphan*/  write_xing; } ;
struct TYPE_23__ {int lsf; int nb_channels; int frame_size; } ;
struct TYPE_22__ {int /*<<< orphan*/  metadata; TYPE_7__* codecpar; } ;
typedef  TYPE_2__ MPADecodeHeader ;
typedef  TYPE_3__ MP3Context ;
typedef  TYPE_4__ AVIOContext ;
typedef  TYPE_5__ AVFormatContext ;
typedef  TYPE_6__ AVDictionaryEntry ;
typedef  TYPE_7__ AVCodecParameters ;

/* Variables and functions */
 int AVIO_SEEKABLE_NORMAL ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int FFABS (int) ; 
 int FFMIN (int,int) ; 
 int FF_ARRAY_ELEMS (int*) ; 
 int INT_MAX ; 
 int MPA_MONO ; 
 int MPA_STEREO ; 
 int XING_SIZE ; 
 int XING_TOC_SIZE ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 TYPE_6__* av_dict_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int avio_close_dyn_buf (TYPE_4__*,char**) ; 
 int avio_open_dyn_buf (TYPE_4__**) ; 
 int /*<<< orphan*/  avio_tell (TYPE_4__*) ; 
 int /*<<< orphan*/  avio_w8 (TYPE_4__*,char) ; 
 int /*<<< orphan*/  avio_wb16 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb24 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (TYPE_4__*,int) ; 
 int /*<<< orphan*/  avio_write (TYPE_4__*,char*,int) ; 
 int*** avpriv_mpa_bitrate_tab ; 
 int* avpriv_mpa_freq_tab ; 
 int avpriv_mpegaudio_decode_header (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ffio_fill (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int** xing_offtbl ; 

__attribute__((used)) static int mp3_write_xing(AVFormatContext *s)
{
    MP3Context       *mp3 = s->priv_data;
    AVCodecParameters *par = s->streams[mp3->audio_stream_idx]->codecpar;
    AVDictionaryEntry *enc = av_dict_get(s->streams[mp3->audio_stream_idx]->metadata, "encoder", NULL, 0);
    AVIOContext *dyn_ctx;
    int32_t        header;
    MPADecodeHeader  mpah;
    int srate_idx, i, channels;
    int bitrate_idx;
    int best_bitrate_idx = -1;
    int best_bitrate_error = INT_MAX;
    int ret;
    int ver = 0;
    int bytes_needed;

    if (!(s->pb->seekable & AVIO_SEEKABLE_NORMAL) || !mp3->write_xing)
        return 0;

    for (i = 0; i < FF_ARRAY_ELEMS(avpriv_mpa_freq_tab); i++) {
        const uint16_t base_freq = avpriv_mpa_freq_tab[i];

        if      (par->sample_rate == base_freq)     ver = 0x3; // MPEG 1
        else if (par->sample_rate == base_freq / 2) ver = 0x2; // MPEG 2
        else if (par->sample_rate == base_freq / 4) ver = 0x0; // MPEG 2.5
        else continue;

        srate_idx = i;
        break;
    }
    if (i == FF_ARRAY_ELEMS(avpriv_mpa_freq_tab)) {
        av_log(s, AV_LOG_WARNING, "Unsupported sample rate, not writing Xing header.\n");
        return -1;
    }

    switch (par->channels) {
    case 1:  channels = MPA_MONO;                                          break;
    case 2:  channels = MPA_STEREO;                                        break;
    default: av_log(s, AV_LOG_WARNING, "Unsupported number of channels, "
                    "not writing Xing header.\n");
             return -1;
    }

    /* dummy MPEG audio header */
    header  =  0xffU                                 << 24; // sync
    header |= (0x7 << 5 | ver << 3 | 0x1 << 1 | 0x1) << 16; // sync/audio-version/layer 3/no crc*/
    header |= (srate_idx << 2) << 8;
    header |= channels << 6;

    for (bitrate_idx = 1; bitrate_idx < 15; bitrate_idx++) {
        int bit_rate = 1000 * avpriv_mpa_bitrate_tab[ver != 3][3 - 1][bitrate_idx];
        int error    = FFABS(bit_rate - par->bit_rate);

        if (error < best_bitrate_error) {
            best_bitrate_error = error;
            best_bitrate_idx   = bitrate_idx;
        }
    }
    av_assert0(best_bitrate_idx >= 0);

    for (bitrate_idx = best_bitrate_idx; ; bitrate_idx++) {
        int32_t mask = bitrate_idx << (4 + 8);
        if (15 == bitrate_idx)
            return -1;
        header |= mask;

        ret = avpriv_mpegaudio_decode_header(&mpah, header);
        av_assert0(ret >= 0);
        mp3->xing_offset = xing_offtbl[mpah.lsf == 1][mpah.nb_channels == 1] + 4;
        bytes_needed     = mp3->xing_offset + XING_SIZE;

        if (bytes_needed <= mpah.frame_size)
            break;

        header &= ~mask;
    }

    ret = avio_open_dyn_buf(&dyn_ctx);
    if (ret < 0)
        return ret;

    avio_wb32(dyn_ctx, header);

    ffio_fill(dyn_ctx, 0, mp3->xing_offset - 4);
    ffio_wfourcc(dyn_ctx, "Xing");
    avio_wb32(dyn_ctx, 0x01 | 0x02 | 0x04 | 0x08);  // frames / size / TOC / vbr scale

    mp3->size = mpah.frame_size;
    mp3->want=1;
    mp3->seen=0;
    mp3->pos=0;

    avio_wb32(dyn_ctx, 0);  // frames
    avio_wb32(dyn_ctx, 0);  // size

    // TOC
    for (i = 0; i < XING_TOC_SIZE; i++)
        avio_w8(dyn_ctx, (uint8_t)(255 * i / XING_TOC_SIZE));

    // vbr quality
    // we write it, because some (broken) tools always expect it to be present
    avio_wb32(dyn_ctx, 0);

    // encoder short version string
    if (enc) {
        uint8_t encoder_str[9] = { 0 };
        if (   strlen(enc->value) > sizeof(encoder_str)
            && !strcmp("Lavc libmp3lame", enc->value)) {
            memcpy(encoder_str, "Lavf lame", 9);
        } else
            memcpy(encoder_str, enc->value, FFMIN(strlen(enc->value), sizeof(encoder_str)));

        avio_write(dyn_ctx, encoder_str, sizeof(encoder_str));
    } else
        avio_write(dyn_ctx, "Lavf\0\0\0\0\0", 9);

    avio_w8(dyn_ctx, 0);      // tag revision 0 / unknown vbr method
    avio_w8(dyn_ctx, 0);      // unknown lowpass filter value
    ffio_fill(dyn_ctx, 0, 8); // empty replaygain fields
    avio_w8(dyn_ctx, 0);      // unknown encoding flags
    avio_w8(dyn_ctx, 0);      // unknown abr/minimal bitrate
    avio_wb24(dyn_ctx, 0);    // empty encoder delay/padding

    avio_w8(dyn_ctx,   0); // misc
    avio_w8(dyn_ctx,   0); // mp3gain
    avio_wb16(dyn_ctx, 0); // preset

    // audio length and CRCs (will be updated later)
    avio_wb32(dyn_ctx, 0); // music length
    avio_wb16(dyn_ctx, 0); // music crc
    avio_wb16(dyn_ctx, 0); // tag crc

    ffio_fill(dyn_ctx, 0, mpah.frame_size - bytes_needed);

    mp3->xing_frame_size   = avio_close_dyn_buf(dyn_ctx, &mp3->xing_frame);
    mp3->xing_frame_offset = avio_tell(s->pb);
    avio_write(s->pb, mp3->xing_frame, mp3->xing_frame_size);

    mp3->audio_size = mp3->xing_frame_size;

    return 0;
}