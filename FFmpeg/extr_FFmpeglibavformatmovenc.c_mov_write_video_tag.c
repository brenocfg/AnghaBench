#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_31__ {scalar_t__ strict_std_compliance; } ;
struct TYPE_30__ {scalar_t__ encryption_scheme; int flags; int /*<<< orphan*/  encryption_kid; TYPE_5__* fc; int /*<<< orphan*/  gamma; } ;
struct TYPE_29__ {scalar_t__ tag; scalar_t__ mode; int height; int* palette; scalar_t__ vos_len; TYPE_2__* par; int /*<<< orphan*/  st; } ;
struct TYPE_27__ {scalar_t__ num; scalar_t__ den; } ;
struct TYPE_28__ {scalar_t__ codec_id; scalar_t__ format; int width; int bits_per_coded_sample; scalar_t__ codec_tag; int field_order; TYPE_1__ sample_aspect_ratio; } ;
typedef  TYPE_3__ MOVTrack ;
typedef  TYPE_4__ MOVMuxContext ;
typedef  int /*<<< orphan*/  AVStereo3D ;
typedef  int /*<<< orphan*/  AVSphericalMapping ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_AV1 ; 
 scalar_t__ AV_CODEC_ID_AVUI ; 
 scalar_t__ AV_CODEC_ID_DNXHD ; 
 scalar_t__ AV_CODEC_ID_H263 ; 
 scalar_t__ AV_CODEC_ID_H264 ; 
 scalar_t__ AV_CODEC_ID_HEVC ; 
 scalar_t__ AV_CODEC_ID_MPEG4 ; 
 scalar_t__ AV_CODEC_ID_R10K ; 
 scalar_t__ AV_CODEC_ID_RAWVIDEO ; 
 scalar_t__ AV_CODEC_ID_SVQ3 ; 
 scalar_t__ AV_CODEC_ID_V210 ; 
 scalar_t__ AV_CODEC_ID_V308 ; 
 scalar_t__ AV_CODEC_ID_V408 ; 
 scalar_t__ AV_CODEC_ID_V410 ; 
 scalar_t__ AV_CODEC_ID_VC1 ; 
 scalar_t__ AV_CODEC_ID_VP6A ; 
 scalar_t__ AV_CODEC_ID_VP6F ; 
 scalar_t__ AV_CODEC_ID_VP9 ; 
 int AV_FIELD_UNKNOWN ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_PIX_FMT_GRAY8 ; 
 scalar_t__ AV_PIX_FMT_PAL8 ; 
 scalar_t__ AV_PIX_FMT_UYVY422 ; 
 scalar_t__ AV_PIX_FMT_YUYV422 ; 
 int /*<<< orphan*/  AV_PKT_DATA_SPHERICAL ; 
 int /*<<< orphan*/  AV_PKT_DATA_STEREO3D ; 
 scalar_t__ FF_COMPLIANCE_UNOFFICIAL ; 
 int FF_MOV_FLAG_WRITE_COLR ; 
 int FF_MOV_FLAG_WRITE_GAMA ; 
 scalar_t__ MKTAG (char,char,char,char) ; 
 scalar_t__ MODE_IPOD ; 
 scalar_t__ MODE_MOV ; 
 scalar_t__ MODE_MP4 ; 
 scalar_t__ MOV_ENC_NONE ; 
 int /*<<< orphan*/  TAG_IS_AVCI (scalar_t__) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ av_stream_get_side_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ff_mov_cenc_write_sinf_tag (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  find_compressor (char*,int,TYPE_3__*) ; 
 int /*<<< orphan*/  mov_write_av1c_tag (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  mov_write_avcc_tag (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  mov_write_avid_tag (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  mov_write_clap_tag (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  mov_write_colr_tag (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  mov_write_d263_tag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mov_write_dpxe_tag (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  mov_write_dvc1_tag (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  mov_write_esds_tag (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  mov_write_extradata_tag (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  mov_write_fiel_tag (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  mov_write_gama_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mov_write_glbl_tag (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  mov_write_hvcc_tag (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  mov_write_pasp_tag (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  mov_write_st3d_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mov_write_sv3d_tag (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mov_write_uuid_tag_ipod (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mov_write_vpcc_tag (TYPE_5__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_video_tag(AVFormatContext *s, AVIOContext *pb, MOVMuxContext *mov, MOVTrack *track)
{
    int64_t pos = avio_tell(pb);
    char compressor_name[32] = { 0 };
    int avid = 0;

    int uncompressed_ycbcr = ((track->par->codec_id == AV_CODEC_ID_RAWVIDEO && track->par->format == AV_PIX_FMT_UYVY422)
                           || (track->par->codec_id == AV_CODEC_ID_RAWVIDEO && track->par->format == AV_PIX_FMT_YUYV422)
                           ||  track->par->codec_id == AV_CODEC_ID_V308
                           ||  track->par->codec_id == AV_CODEC_ID_V408
                           ||  track->par->codec_id == AV_CODEC_ID_V410
                           ||  track->par->codec_id == AV_CODEC_ID_V210);

    avio_wb32(pb, 0); /* size */
    if (mov->encryption_scheme != MOV_ENC_NONE) {
        ffio_wfourcc(pb, "encv");
    } else {
        avio_wl32(pb, track->tag); // store it byteswapped
    }
    avio_wb32(pb, 0); /* Reserved */
    avio_wb16(pb, 0); /* Reserved */
    avio_wb16(pb, 1); /* Data-reference index */

    if (uncompressed_ycbcr) {
        avio_wb16(pb, 2); /* Codec stream version */
    } else {
        avio_wb16(pb, 0); /* Codec stream version */
    }
    avio_wb16(pb, 0); /* Codec stream revision (=0) */
    if (track->mode == MODE_MOV) {
        ffio_wfourcc(pb, "FFMP"); /* Vendor */
        if (track->par->codec_id == AV_CODEC_ID_RAWVIDEO || uncompressed_ycbcr) {
            avio_wb32(pb, 0); /* Temporal Quality */
            avio_wb32(pb, 0x400); /* Spatial Quality = lossless*/
        } else {
            avio_wb32(pb, 0x200); /* Temporal Quality = normal */
            avio_wb32(pb, 0x200); /* Spatial Quality = normal */
        }
    } else {
        avio_wb32(pb, 0); /* Reserved */
        avio_wb32(pb, 0); /* Reserved */
        avio_wb32(pb, 0); /* Reserved */
    }
    avio_wb16(pb, track->par->width); /* Video width */
    avio_wb16(pb, track->height); /* Video height */
    avio_wb32(pb, 0x00480000); /* Horizontal resolution 72dpi */
    avio_wb32(pb, 0x00480000); /* Vertical resolution 72dpi */
    avio_wb32(pb, 0); /* Data size (= 0) */
    avio_wb16(pb, 1); /* Frame count (= 1) */

    /* FIXME not sure, ISO 14496-1 draft where it shall be set to 0 */
    find_compressor(compressor_name, 32, track);
    avio_w8(pb, strlen(compressor_name));
    avio_write(pb, compressor_name, 31);

    if (track->mode == MODE_MOV &&
       (track->par->codec_id == AV_CODEC_ID_V410 || track->par->codec_id == AV_CODEC_ID_V210))
        avio_wb16(pb, 0x18);
    else if (track->mode == MODE_MOV && track->par->bits_per_coded_sample)
        avio_wb16(pb, track->par->bits_per_coded_sample |
                  (track->par->format == AV_PIX_FMT_GRAY8 ? 0x20 : 0));
    else
        avio_wb16(pb, 0x18); /* Reserved */

    if (track->mode == MODE_MOV && track->par->format == AV_PIX_FMT_PAL8) {
        int pal_size = 1 << track->par->bits_per_coded_sample;
        int i;
        avio_wb16(pb, 0);             /* Color table ID */
        avio_wb32(pb, 0);             /* Color table seed */
        avio_wb16(pb, 0x8000);        /* Color table flags */
        avio_wb16(pb, pal_size - 1);  /* Color table size (zero-relative) */
        for (i = 0; i < pal_size; i++) {
            uint32_t rgb = track->palette[i];
            uint16_t r = (rgb >> 16) & 0xff;
            uint16_t g = (rgb >> 8)  & 0xff;
            uint16_t b = rgb         & 0xff;
            avio_wb16(pb, 0);
            avio_wb16(pb, (r << 8) | r);
            avio_wb16(pb, (g << 8) | g);
            avio_wb16(pb, (b << 8) | b);
        }
    } else
        avio_wb16(pb, 0xffff); /* Reserved */

    if (track->tag == MKTAG('m','p','4','v'))
        mov_write_esds_tag(pb, track);
    else if (track->par->codec_id == AV_CODEC_ID_H263)
        mov_write_d263_tag(pb);
    else if (track->par->codec_id == AV_CODEC_ID_AVUI ||
            track->par->codec_id == AV_CODEC_ID_SVQ3) {
        mov_write_extradata_tag(pb, track);
        avio_wb32(pb, 0);
    } else if (track->par->codec_id == AV_CODEC_ID_DNXHD) {
        mov_write_avid_tag(pb, track);
        avid = 1;
    } else if (track->par->codec_id == AV_CODEC_ID_HEVC)
        mov_write_hvcc_tag(pb, track);
    else if (track->par->codec_id == AV_CODEC_ID_H264 && !TAG_IS_AVCI(track->tag)) {
        mov_write_avcc_tag(pb, track);
        if (track->mode == MODE_IPOD)
            mov_write_uuid_tag_ipod(pb);
    } else if (track->par->codec_id == AV_CODEC_ID_VP9) {
        mov_write_vpcc_tag(mov->fc, pb, track);
    } else if (track->par->codec_id == AV_CODEC_ID_AV1) {
        mov_write_av1c_tag(pb, track);
    } else if (track->par->codec_id == AV_CODEC_ID_VC1 && track->vos_len > 0)
        mov_write_dvc1_tag(pb, track);
    else if (track->par->codec_id == AV_CODEC_ID_VP6F ||
             track->par->codec_id == AV_CODEC_ID_VP6A) {
        /* Don't write any potential extradata here - the cropping
         * is signalled via the normal width/height fields. */
    } else if (track->par->codec_id == AV_CODEC_ID_R10K) {
        if (track->par->codec_tag == MKTAG('R','1','0','k'))
            mov_write_dpxe_tag(pb, track);
    } else if (track->vos_len > 0)
        mov_write_glbl_tag(pb, track);

    if (track->par->codec_id != AV_CODEC_ID_H264 &&
        track->par->codec_id != AV_CODEC_ID_MPEG4 &&
        track->par->codec_id != AV_CODEC_ID_DNXHD) {
        int field_order = track->par->field_order;

#if FF_API_LAVF_AVCTX
    FF_DISABLE_DEPRECATION_WARNINGS
    if (field_order != track->st->codec->field_order && track->st->codec->field_order != AV_FIELD_UNKNOWN)
        field_order = track->st->codec->field_order;
    FF_ENABLE_DEPRECATION_WARNINGS
#endif

        if (field_order != AV_FIELD_UNKNOWN)
            mov_write_fiel_tag(pb, track, field_order);
    }

    if (mov->flags & FF_MOV_FLAG_WRITE_GAMA) {
        if (track->mode == MODE_MOV)
            mov_write_gama_tag(s, pb, track, mov->gamma);
        else
            av_log(mov->fc, AV_LOG_WARNING, "Not writing 'gama' atom. Format is not MOV.\n");
    }
    if (mov->flags & FF_MOV_FLAG_WRITE_COLR) {
        if (track->mode == MODE_MOV || track->mode == MODE_MP4)
            mov_write_colr_tag(pb, track);
        else
            av_log(mov->fc, AV_LOG_WARNING, "Not writing 'colr' atom. Format is not MOV or MP4.\n");
    }

    if (track->mode == MODE_MP4 && mov->fc->strict_std_compliance <= FF_COMPLIANCE_UNOFFICIAL) {
        AVStereo3D* stereo_3d = (AVStereo3D*) av_stream_get_side_data(track->st, AV_PKT_DATA_STEREO3D, NULL);
        AVSphericalMapping* spherical_mapping = (AVSphericalMapping*)av_stream_get_side_data(track->st, AV_PKT_DATA_SPHERICAL, NULL);

        if (stereo_3d)
            mov_write_st3d_tag(s, pb, stereo_3d);
        if (spherical_mapping)
            mov_write_sv3d_tag(mov->fc, pb, spherical_mapping);
    }

    if (track->par->sample_aspect_ratio.den && track->par->sample_aspect_ratio.num) {
        mov_write_pasp_tag(pb, track);
    }

    if (uncompressed_ycbcr){
        mov_write_clap_tag(pb, track);
    }

    if (mov->encryption_scheme != MOV_ENC_NONE) {
        ff_mov_cenc_write_sinf_tag(track, pb, mov->encryption_kid);
    }

    /* extra padding for avid stsd */
    /* https://developer.apple.com/library/mac/documentation/QuickTime/QTFF/QTFFChap2/qtff2.html#//apple_ref/doc/uid/TP40000939-CH204-61112 */
    if (avid)
        avio_wb32(pb, 0);

    return update_size(pb, pos);
}