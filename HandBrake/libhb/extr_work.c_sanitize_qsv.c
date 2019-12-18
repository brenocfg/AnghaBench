#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ decode; } ;
struct TYPE_16__ {int vcodec; TYPE_3__* title; int /*<<< orphan*/ * list_filter; TYPE_1__ qsv; } ;
typedef  TYPE_4__ hb_job_t ;
struct TYPE_17__ {int id; int /*<<< orphan*/  name; int /*<<< orphan*/  settings; } ;
typedef  TYPE_5__ hb_filter_object_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;
struct TYPE_14__ {int width; int height; } ;
struct TYPE_15__ {int* crop; TYPE_2__ geometry; } ;

/* Variables and functions */
 scalar_t__ HB_CPU_PLATFORM_INTEL_IVB ; 
#define  HB_FILTER_AVFILTER 132 
#define  HB_FILTER_CROP_SCALE 131 
#define  HB_FILTER_DEINTERLACE 130 
 int /*<<< orphan*/  HB_FILTER_QSV ; 
 int /*<<< orphan*/  HB_FILTER_QSV_POST ; 
 int /*<<< orphan*/  HB_FILTER_QSV_PRE ; 
#define  HB_FILTER_RENDER_SUB 129 
#define  HB_FILTER_ROTATE 128 
 int HB_VCODEC_QSV_MASK ; 
 int MODE_DEINTERLACE_QSV ; 
 int /*<<< orphan*/  hb_add_filter_dict (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_dict_extract_int (int*,int /*<<< orphan*/ ,char*) ; 
 int hb_dict_get_int (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * hb_dict_init () ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_filter_close (TYPE_5__**) ; 
 TYPE_5__* hb_filter_init (int /*<<< orphan*/ ) ; 
 scalar_t__ hb_get_cpu_platform () ; 
 int hb_list_count (int /*<<< orphan*/ *) ; 
 TYPE_5__* hb_list_item (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hb_list_rem (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  hb_log (char*,...) ; 
 scalar_t__ hb_qsv_copyframe_is_slow (int) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hb_value_int (int) ; 

__attribute__((used)) static int sanitize_qsv( hb_job_t * job )
{
#if HB_PROJECT_FEATURE_QSV
#if 0 // TODO: re-implement QSV VPP filtering and QSV zerocopy path
    int i;

    /*
     * XXX: mfxCoreInterface's CopyFrame doesn't work in old drivers, and our
     *      workaround is really slow. If we have validated CPU-based filters in
     *      the list and we can't use CopyFrame, disable QSV decoding until a
     *      better solution is implemented.
     */
    if (hb_qsv_copyframe_is_slow(job->vcodec))
    {
        if (job->list_filter != NULL)
        {
            int encode_only = 0;
            for (i = 0; i < hb_list_count(job->list_filter) && !encode_only; i++)
            {
                hb_filter_object_t *filter = hb_list_item(job->list_filter, i);
                switch (filter->id)
                {
                    // validated, CPU-based filters
                    case HB_FILTER_ROTATE:
                    case HB_FILTER_RENDER_SUB:
                    case HB_FILTER_AVFILTER:
                        encode_only = 1;
                        break;

                    // CPU-based deinterlace (validated)
                    case HB_FILTER_DEINTERLACE:
                    {
                        int mode = hb_dict_get_int(filter->settings, "mode");
                        if (!(mode & MODE_DEINTERLACE_QSV))
                        {
                            encode_only = 1;
                        }
                    } break;

                    // other filters will be removed
                    default:
                        break;
                }
            }
            if (encode_only)
            {
                hb_log("do_job: QSV: possible CopyFrame bug, using encode-only path");
                if (hb_get_cpu_platform() >= HB_CPU_PLATFORM_INTEL_IVB)
                {
                    hb_log("do_job: QSV: please update your Intel graphics driver to version 9.18.10.3257 or later");
                }
                job->qsv.decode = 0;
            }
        }
    }

    /*
     * When QSV's VPP is used for filtering, not all CPU filters
     * are supported, so we need to do a little extra setup here.
     */
    if (job->vcodec & HB_VCODEC_QSV_MASK)
    {
        int vpp_settings[7];
        int num_cpu_filters = 0;
        hb_filter_object_t *filter;
        // default values for VPP filter
        vpp_settings[0] = job->title->geometry.width;
        vpp_settings[1] = job->title->geometry.height;
        vpp_settings[2] = job->title->crop[0];
        vpp_settings[3] = job->title->crop[1];
        vpp_settings[4] = job->title->crop[2];
        vpp_settings[5] = job->title->crop[3];
        vpp_settings[6] = 0; // deinterlace: off
        if (job->list_filter != NULL && hb_list_count(job->list_filter) > 0)
        {
            while (hb_list_count(job->list_filter) > num_cpu_filters)
            {
                filter = hb_list_item(job->list_filter, num_cpu_filters);
                switch (filter->id)
                {
                    // cropping and scaling always done via VPP filter
                    case HB_FILTER_CROP_SCALE:
                        hb_dict_extract_int(&vpp_settings[0], filter->settings,
                                            "width");
                        hb_dict_extract_int(&vpp_settings[1], filter->settings,
                                            "height");
                        hb_dict_extract_int(&vpp_settings[2], filter->settings,
                                            "crop-top");
                        hb_dict_extract_int(&vpp_settings[3], filter->settings,
                                            "crop-bottom");
                        hb_dict_extract_int(&vpp_settings[4], filter->settings,
                                            "crop-left");
                        hb_dict_extract_int(&vpp_settings[5], filter->settings,
                                            "crop-right");

                        hb_list_rem(job->list_filter, filter);
                        hb_filter_close(&filter);
                        break;

                    // pick VPP or CPU deinterlace depending on settings
                    case HB_FILTER_DEINTERLACE:
                    {
                        int mode = hb_dict_get_int(filter->settings, "mode");
                        if (mode & MODE_DEINTERLACE_QSV)
                        {
                            // deinterlacing via VPP filter
                            vpp_settings[6] = 1;
                            hb_list_rem(job->list_filter, filter);
                            hb_filter_close(&filter);
                        }
                        else
                        {
                            // validated
                            num_cpu_filters++;
                        }
                    } break;

                    // then, validated filters
                    case HB_FILTER_ROTATE: // TODO: use Media SDK for this
                    case HB_FILTER_RENDER_SUB:
                    case HB_FILTER_AVFILTER:
                        num_cpu_filters++;
                        break;

                    // finally, drop all unsupported filters
                    default:
                        hb_log("do_job: QSV: full path, removing unsupported filter '%s'",
                               filter->name);
                        hb_list_rem(job->list_filter, filter);
                        hb_filter_close(&filter);
                        break;
                }
            }
            if (num_cpu_filters > 0)
            {
                // we need filters to copy to system memory and back
                filter = hb_filter_init(HB_FILTER_QSV_PRE);
                hb_add_filter_dict(job, filter, NULL);
                filter = hb_filter_init(HB_FILTER_QSV_POST);
                hb_add_filter_dict(job, filter, NULL);
            }
            if (vpp_settings[0] != job->title->geometry.width  ||
                vpp_settings[1] != job->title->geometry.height ||
                vpp_settings[2] >= 1 /* crop */       ||
                vpp_settings[3] >= 1 /* crop */       ||
                vpp_settings[4] >= 1 /* crop */       ||
                vpp_settings[5] >= 1 /* crop */       ||
                vpp_settings[6] >= 1 /* deinterlace */)
            {
                // we need the VPP filter
                hb_dict_t * dict = hb_dict_init();
                hb_dict_set(dict, "width", hb_value_int(vpp_settings[0]));
                hb_dict_set(dict, "height", hb_value_int(vpp_settings[1]));
                hb_dict_set(dict, "crop-top", hb_value_int(vpp_settings[2]));
                hb_dict_set(dict, "crop-bottom", hb_value_int(vpp_settings[3]));
                hb_dict_set(dict, "crop-left", hb_value_int(vpp_settings[4]));
                hb_dict_set(dict, "crop-right", hb_value_int(vpp_settings[5]));
                hb_dict_set(dict, "deinterlace", hb_value_int(vpp_settings[6]));

                filter = hb_filter_init(HB_FILTER_QSV);
                hb_add_filter_dict(job, filter, dict);
                hb_value_free(&dict);
            }
        }
    }
#endif // QSV VPP filtering and QSV zerocopy path
#endif // HB_PROJECT_FEATURE_QSV

    return 0;
}