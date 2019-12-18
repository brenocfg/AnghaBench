#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_22__ {scalar_t__ encryption_scheme; int /*<<< orphan*/  encryption_kid; } ;
struct TYPE_21__ {scalar_t__ tag; scalar_t__ mode; int timescale; int sample_size; scalar_t__ vos_len; TYPE_1__* par; scalar_t__ audio_vbr; } ;
struct TYPE_20__ {int channels; scalar_t__ codec_id; int sample_rate; int bits_per_coded_sample; int bits_per_raw_sample; int frame_size; scalar_t__ codec_type; } ;
typedef  TYPE_2__ MOVTrack ;
typedef  TYPE_3__ MOVMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AV_CODEC_ID_AAC ; 
 scalar_t__ AV_CODEC_ID_AC3 ; 
 scalar_t__ AV_CODEC_ID_ADPCM_G726 ; 
 scalar_t__ AV_CODEC_ID_ADPCM_IMA_WAV ; 
 scalar_t__ AV_CODEC_ID_ADPCM_MS ; 
 scalar_t__ AV_CODEC_ID_ALAC ; 
 scalar_t__ AV_CODEC_ID_AMR_NB ; 
 scalar_t__ AV_CODEC_ID_EAC3 ; 
 scalar_t__ AV_CODEC_ID_FLAC ; 
 scalar_t__ AV_CODEC_ID_OPUS ; 
 scalar_t__ AV_CODEC_ID_PCM_S8 ; 
 scalar_t__ AV_CODEC_ID_PCM_U8 ; 
 scalar_t__ AV_CODEC_ID_QDM2 ; 
 scalar_t__ AV_CODEC_ID_TRUEHD ; 
 scalar_t__ AV_CODEC_ID_WMAPRO ; 
 scalar_t__ AV_RL32 (char*) ; 
 scalar_t__ MKTAG (char,char,char,char) ; 
 scalar_t__ MODE_MOV ; 
 scalar_t__ MOV_ENC_NONE ; 
 int UINT16_MAX ; 
 int /*<<< orphan*/  av_double2int (int) ; 
 int av_get_bits_per_sample (scalar_t__) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int ff_mov_cenc_write_sinf_tag (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int get_samples_per_packet (TYPE_2__*) ; 
 int mov_get_lpcm_flags (scalar_t__) ; 
 scalar_t__ mov_pcm_be_gt16 (scalar_t__) ; 
 scalar_t__ mov_pcm_le_gt16 (scalar_t__) ; 
 int mov_write_ac3_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int mov_write_amr_tag (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int mov_write_chan_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int mov_write_dfla_tag (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int mov_write_dmlp_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int mov_write_dops_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int mov_write_eac3_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int mov_write_esds_tag (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int mov_write_extradata_tag (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int mov_write_glbl_tag (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int mov_write_wave_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int mov_write_wfex_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_audio_tag(AVFormatContext *s, AVIOContext *pb, MOVMuxContext *mov, MOVTrack *track)
{
    int64_t pos = avio_tell(pb);
    int version = 0;
    uint32_t tag = track->tag;
    int ret = 0;

    if (track->mode == MODE_MOV) {
        if (track->timescale > UINT16_MAX || !track->par->channels) {
            if (mov_get_lpcm_flags(track->par->codec_id))
                tag = AV_RL32("lpcm");
            version = 2;
        } else if (track->audio_vbr || mov_pcm_le_gt16(track->par->codec_id) ||
                   mov_pcm_be_gt16(track->par->codec_id) ||
                   track->par->codec_id == AV_CODEC_ID_ADPCM_MS ||
                   track->par->codec_id == AV_CODEC_ID_ADPCM_IMA_WAV ||
                   track->par->codec_id == AV_CODEC_ID_QDM2) {
            version = 1;
        }
    }

    avio_wb32(pb, 0); /* size */
    if (mov->encryption_scheme != MOV_ENC_NONE) {
        ffio_wfourcc(pb, "enca");
    } else {
        avio_wl32(pb, tag); // store it byteswapped
    }
    avio_wb32(pb, 0); /* Reserved */
    avio_wb16(pb, 0); /* Reserved */
    avio_wb16(pb, 1); /* Data-reference index, XXX  == 1 */

    /* SoundDescription */
    avio_wb16(pb, version); /* Version */
    avio_wb16(pb, 0); /* Revision level */
    avio_wb32(pb, 0); /* Reserved */

    if (version == 2) {
        avio_wb16(pb, 3);
        avio_wb16(pb, 16);
        avio_wb16(pb, 0xfffe);
        avio_wb16(pb, 0);
        avio_wb32(pb, 0x00010000);
        avio_wb32(pb, 72);
        avio_wb64(pb, av_double2int(track->par->sample_rate));
        avio_wb32(pb, track->par->channels);
        avio_wb32(pb, 0x7F000000);
        avio_wb32(pb, av_get_bits_per_sample(track->par->codec_id));
        avio_wb32(pb, mov_get_lpcm_flags(track->par->codec_id));
        avio_wb32(pb, track->sample_size);
        avio_wb32(pb, get_samples_per_packet(track));
    } else {
        if (track->mode == MODE_MOV) {
            avio_wb16(pb, track->par->channels);
            if (track->par->codec_id == AV_CODEC_ID_PCM_U8 ||
                track->par->codec_id == AV_CODEC_ID_PCM_S8)
                avio_wb16(pb, 8); /* bits per sample */
            else if (track->par->codec_id == AV_CODEC_ID_ADPCM_G726)
                avio_wb16(pb, track->par->bits_per_coded_sample);
            else
                avio_wb16(pb, 16);
            avio_wb16(pb, track->audio_vbr ? -2 : 0); /* compression ID */
        } else { /* reserved for mp4/3gp */
            if (track->par->codec_id == AV_CODEC_ID_FLAC ||
                track->par->codec_id == AV_CODEC_ID_ALAC ||
                track->par->codec_id == AV_CODEC_ID_OPUS) {
                avio_wb16(pb, track->par->channels);
            } else {
                avio_wb16(pb, 2);
            }
            if (track->par->codec_id == AV_CODEC_ID_FLAC ||
                track->par->codec_id == AV_CODEC_ID_ALAC) {
                avio_wb16(pb, track->par->bits_per_raw_sample);
            } else {
                avio_wb16(pb, 16);
            }
            avio_wb16(pb, 0);
        }

        avio_wb16(pb, 0); /* packet size (= 0) */
        if (track->par->codec_id == AV_CODEC_ID_OPUS)
            avio_wb16(pb, 48000);
        else if (track->par->codec_id == AV_CODEC_ID_TRUEHD)
            avio_wb32(pb, track->par->sample_rate);
        else
            avio_wb16(pb, track->par->sample_rate <= UINT16_MAX ?
                          track->par->sample_rate : 0);

        if (track->par->codec_id != AV_CODEC_ID_TRUEHD)
            avio_wb16(pb, 0); /* Reserved */
    }

    if (version == 1) { /* SoundDescription V1 extended info */
        if (mov_pcm_le_gt16(track->par->codec_id) ||
            mov_pcm_be_gt16(track->par->codec_id))
            avio_wb32(pb, 1); /*  must be 1 for  uncompressed formats */
        else
            avio_wb32(pb, track->par->frame_size); /* Samples per packet */
        avio_wb32(pb, track->sample_size / track->par->channels); /* Bytes per packet */
        avio_wb32(pb, track->sample_size); /* Bytes per frame */
        avio_wb32(pb, 2); /* Bytes per sample */
    }

    if (track->mode == MODE_MOV &&
        (track->par->codec_id == AV_CODEC_ID_AAC           ||
         track->par->codec_id == AV_CODEC_ID_AC3           ||
         track->par->codec_id == AV_CODEC_ID_EAC3          ||
         track->par->codec_id == AV_CODEC_ID_AMR_NB        ||
         track->par->codec_id == AV_CODEC_ID_ALAC          ||
         track->par->codec_id == AV_CODEC_ID_ADPCM_MS      ||
         track->par->codec_id == AV_CODEC_ID_ADPCM_IMA_WAV ||
         track->par->codec_id == AV_CODEC_ID_QDM2          ||
         (mov_pcm_le_gt16(track->par->codec_id) && version==1) ||
         (mov_pcm_be_gt16(track->par->codec_id) && version==1)))
        ret = mov_write_wave_tag(s, pb, track);
    else if (track->tag == MKTAG('m','p','4','a'))
        ret = mov_write_esds_tag(pb, track);
    else if (track->par->codec_id == AV_CODEC_ID_AMR_NB)
        ret = mov_write_amr_tag(pb, track);
    else if (track->par->codec_id == AV_CODEC_ID_AC3)
        ret = mov_write_ac3_tag(s, pb, track);
    else if (track->par->codec_id == AV_CODEC_ID_EAC3)
        ret = mov_write_eac3_tag(s, pb, track);
    else if (track->par->codec_id == AV_CODEC_ID_ALAC)
        ret = mov_write_extradata_tag(pb, track);
    else if (track->par->codec_id == AV_CODEC_ID_WMAPRO)
        ret = mov_write_wfex_tag(s, pb, track);
    else if (track->par->codec_id == AV_CODEC_ID_FLAC)
        ret = mov_write_dfla_tag(pb, track);
    else if (track->par->codec_id == AV_CODEC_ID_OPUS)
        ret = mov_write_dops_tag(s, pb, track);
    else if (track->par->codec_id == AV_CODEC_ID_TRUEHD)
        ret = mov_write_dmlp_tag(s, pb, track);
    else if (track->vos_len > 0)
        ret = mov_write_glbl_tag(pb, track);

    if (ret < 0)
        return ret;

    if (track->mode == MODE_MOV && track->par->codec_type == AVMEDIA_TYPE_AUDIO
            && ((ret = mov_write_chan_tag(s, pb, track)) < 0)) {
        return ret;
    }

    if (mov->encryption_scheme != MOV_ENC_NONE
            && ((ret = ff_mov_cenc_write_sinf_tag(track, pb, mov->encryption_kid)) < 0)) {
        return ret;
    }

    ret = update_size(pb, pos);
    return ret;
}