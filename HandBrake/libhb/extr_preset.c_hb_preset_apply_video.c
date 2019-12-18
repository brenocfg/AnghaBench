#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const hb_value_t ;
struct TYPE_3__ {int muxers; int /*<<< orphan*/  short_name; } ;
typedef  TYPE_1__ hb_encoder_t ;
typedef  int /*<<< orphan*/  const hb_dict_t ;

/* Variables and functions */
 int HB_COLR_MAT_BT2020_NCL ; 
 int HB_COLR_MAT_BT709 ; 
 int HB_COLR_MAT_SMPTE170M ; 
 int HB_COLR_PRI_BT2020 ; 
 int HB_COLR_PRI_BT709 ; 
 int HB_COLR_PRI_EBUTECH ; 
 int HB_COLR_PRI_SMPTEC ; 
 int HB_COLR_TRA_BT709 ; 
 int /*<<< orphan*/  HB_VALUE_TYPE_BOOL ; 
 int /*<<< orphan*/  HB_VALUE_TYPE_DOUBLE ; 
 int /*<<< orphan*/  HB_VALUE_TYPE_INT ; 
 scalar_t__ HB_VALUE_TYPE_STRING ; 
 int HB_VCODEC_X264_MASK ; 
 int /*<<< orphan*/  free (char*) ; 
 int hb_container_get_from_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_container_get_name (int) ; 
 int /*<<< orphan*/  const* hb_dict_get (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  const* hb_dict_init () ; 
 int /*<<< orphan*/  hb_dict_remove (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hb_error (char*,char*,...) ; 
 int /*<<< orphan*/  const* hb_value_dup (int /*<<< orphan*/  const*) ; 
 scalar_t__ hb_value_get_bool (int /*<<< orphan*/  const*) ; 
 scalar_t__ hb_value_get_double (int /*<<< orphan*/  const*) ; 
 int hb_value_get_int (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hb_value_get_string (int /*<<< orphan*/  const*) ; 
 char* hb_value_get_string_xform (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* hb_value_int (int) ; 
 int /*<<< orphan*/  const* hb_value_string (int /*<<< orphan*/ ) ; 
 scalar_t__ hb_value_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* hb_value_xform (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* hb_video_encoder_get_from_codec (int) ; 
 int hb_video_encoder_get_from_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_video_encoder_get_name (int) ; 

int hb_preset_apply_video(const hb_dict_t *preset, hb_dict_t *job_dict)
{
    hb_dict_t    *dest_dict, *video_dict, *qsv;
    hb_value_t   *value, *vcodec_value;
    int           mux, vcodec, vqtype, color_matrix_code;
    hb_encoder_t *encoder;

    dest_dict    = hb_dict_get(job_dict, "Destination");
    mux          = hb_container_get_from_name(hb_value_get_string(
                                                hb_dict_get(dest_dict, "Mux")));
    vcodec_value = hb_dict_get(preset, "VideoEncoder");
    if (hb_value_type(vcodec_value) == HB_VALUE_TYPE_STRING)
    {
        vcodec = hb_video_encoder_get_from_name(
                    hb_value_get_string(vcodec_value));
    }
    else
    {
        vcodec = hb_value_get_int(vcodec_value);
    }
    encoder = hb_video_encoder_get_from_codec(vcodec);
    if (encoder == NULL)
    {
        char *str = hb_value_get_string_xform(vcodec_value);
        hb_error("Invalid video encoder (%s)", str);
        free(str);
        return -1;
    }
    if (!(encoder->muxers & mux))
    {
        hb_error("Incompatible video encoder (%s) for muxer (%s)",
                  hb_video_encoder_get_name(vcodec),
                  hb_container_get_name(mux));
        return -1;
    }

    video_dict = hb_dict_get(job_dict, "Video");
    hb_dict_set(video_dict, "Encoder", hb_value_string(encoder->short_name));

    color_matrix_code = hb_value_get_int(hb_dict_get(preset, "VideoColorMatrixCodeOveride"));
    if (color_matrix_code != 0)
    {
        int color_prim, color_transfer, color_matrix;

        switch (color_matrix_code)
        {
            case 4:
                // ITU BT.2020 UHD content
                color_prim      = HB_COLR_PRI_BT2020;
                color_transfer  = HB_COLR_TRA_BT709;
                color_matrix    = HB_COLR_MAT_BT2020_NCL;
                break;
            case 3:
                // ITU BT.709 HD content
                color_prim      = HB_COLR_PRI_BT709;
                color_transfer  = HB_COLR_TRA_BT709;
                color_matrix    = HB_COLR_MAT_BT709;
                break;
            case 2:
                // ITU BT.601 DVD or SD TV content (PAL)
                color_prim      = HB_COLR_PRI_EBUTECH;
                color_transfer  = HB_COLR_TRA_BT709;
                color_matrix    = HB_COLR_MAT_SMPTE170M;
                break;
            case 1:
            default:
                // ITU BT.601 DVD or SD TV content (NTSC)
                color_prim      = HB_COLR_PRI_SMPTEC;
                color_transfer  = HB_COLR_TRA_BT709;
                color_matrix    = HB_COLR_MAT_SMPTE170M;
                break;
        }

        hb_dict_set(video_dict, "ColorPrimariesOverride",
                    hb_value_int(color_prim));
        hb_dict_set(video_dict, "ColorTransferOverride",
                    hb_value_int(color_transfer));
        hb_dict_set(video_dict, "ColorMatrixOverride",
                    hb_value_int(color_matrix));
    }
    hb_dict_set(video_dict, "Encoder", hb_value_dup(vcodec_value));

    if ((vcodec & HB_VCODEC_X264_MASK) &&
        hb_value_get_bool(hb_dict_get(preset, "x264UseAdvancedOptions")))
    {
        hb_dict_set(video_dict, "Options",
                    hb_value_dup(hb_dict_get(preset, "x264Option")));
    }
    else
    {
        if ((value = hb_dict_get(preset, "VideoPreset")) != NULL)
            hb_dict_set(video_dict, "Preset", hb_value_dup(value));
        if ((value = hb_dict_get(preset, "VideoProfile")) != NULL)
            hb_dict_set(video_dict, "Profile", hb_value_dup(value));
        if ((value = hb_dict_get(preset, "VideoLevel")) != NULL)
            hb_dict_set(video_dict, "Level", hb_value_dup(value));
        if ((value = hb_dict_get(preset, "VideoTune")) != NULL)
            hb_dict_set(video_dict, "Tune", hb_value_dup(value));
        if ((value = hb_dict_get(preset, "VideoOptionExtra")) != NULL)
            hb_dict_set(video_dict, "Options", hb_value_dup(value));
    }

    vqtype = hb_value_get_int(hb_dict_get(preset, "VideoQualityType"));
    if (vqtype == 2)        // Constant quality
    {
        hb_dict_set(video_dict, "Quality",
                    hb_value_xform(hb_dict_get(preset, "VideoQualitySlider"),
                                   HB_VALUE_TYPE_DOUBLE));
        hb_dict_remove(video_dict, "Bitrate");
    }
    else if (vqtype == 1)   // ABR
    {
        hb_dict_set(video_dict, "Bitrate",
                    hb_value_xform(hb_dict_get(preset, "VideoAvgBitrate"),
                                   HB_VALUE_TYPE_INT));
        hb_dict_set(video_dict, "TwoPass",
                    hb_value_xform(hb_dict_get(preset, "VideoTwoPass"),
                                   HB_VALUE_TYPE_BOOL));
        hb_dict_set(video_dict, "Turbo",
                    hb_value_xform(hb_dict_get(preset, "VideoTurboTwoPass"),
                                   HB_VALUE_TYPE_BOOL));
        hb_dict_remove(video_dict, "Quality");
    }
    else
    {
        value = hb_dict_get(preset, "VideoQualitySlider");
        if (value != NULL && hb_value_get_double(value) >= 0)
        {
            hb_dict_set(video_dict, "Quality",
                        hb_value_xform(value, HB_VALUE_TYPE_DOUBLE));
            hb_dict_remove(video_dict, "Bitrate");
        }
        else
        {
            hb_dict_set(video_dict, "Bitrate",
                        hb_value_xform(hb_dict_get(preset, "VideoAvgBitrate"),
                                       HB_VALUE_TYPE_INT));
            hb_dict_set(video_dict, "TwoPass",
                        hb_value_xform(hb_dict_get(preset, "VideoTwoPass"),
                                       HB_VALUE_TYPE_BOOL));
            hb_dict_set(video_dict, "Turbo",
                        hb_value_xform(hb_dict_get(preset, "VideoTurboTwoPass"),
                                       HB_VALUE_TYPE_BOOL));
            hb_dict_remove(video_dict, "Quality");
        }
    }
    qsv = hb_dict_get(video_dict, "QSV");
    if (qsv == NULL)
    {
        qsv = hb_dict_init();
        hb_dict_set(video_dict, "QSV", qsv);
    }
    if ((value = hb_dict_get(preset, "VideoQSVDecode")) != NULL)
    {
        hb_dict_set(qsv, "Decode",
                    hb_value_xform(value, HB_VALUE_TYPE_BOOL));
    }
    if ((value = hb_dict_get(preset, "VideoQSVLowPower")) != NULL)
    {
        hb_dict_set(qsv, "LowPower",
                    hb_value_xform(value, HB_VALUE_TYPE_BOOL));
    }
     if ((value = hb_dict_get(preset, "VideoQSVAsyncDepth")) != NULL)
    {
        hb_dict_set(qsv, "AsyncDepth",
                    hb_value_xform(value, HB_VALUE_TYPE_INT));
    }

    return 0;
}