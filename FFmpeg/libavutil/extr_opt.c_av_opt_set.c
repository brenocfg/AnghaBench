#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  double int64_t ;
struct TYPE_16__ {int type; int flags; int offset; double min; double max; int /*<<< orphan*/  name; int /*<<< orphan*/  help; } ;
struct TYPE_15__ {int /*<<< orphan*/  num; int /*<<< orphan*/  den; } ;
typedef  TYPE_1__ AVRational ;
typedef  TYPE_2__ AVOption ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_OPTION_NOT_FOUND ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int AV_OPT_FLAG_DEPRECATED ; 
 int AV_OPT_FLAG_READONLY ; 
#define  AV_OPT_TYPE_BINARY 144 
#define  AV_OPT_TYPE_BOOL 143 
#define  AV_OPT_TYPE_CHANNEL_LAYOUT 142 
#define  AV_OPT_TYPE_COLOR 141 
#define  AV_OPT_TYPE_DOUBLE 140 
#define  AV_OPT_TYPE_DURATION 139 
#define  AV_OPT_TYPE_FLAGS 138 
#define  AV_OPT_TYPE_FLOAT 137 
#define  AV_OPT_TYPE_IMAGE_SIZE 136 
#define  AV_OPT_TYPE_INT 135 
#define  AV_OPT_TYPE_INT64 134 
#define  AV_OPT_TYPE_PIXEL_FMT 133 
#define  AV_OPT_TYPE_RATIONAL 132 
#define  AV_OPT_TYPE_SAMPLE_FMT 131 
#define  AV_OPT_TYPE_STRING 130 
#define  AV_OPT_TYPE_UINT64 129 
#define  AV_OPT_TYPE_VIDEO_RATE 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERANGE ; 
 double av_get_channel_layout (char const*) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* av_opt_find2 (void*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,void**) ; 
 int av_parse_time (double*,char const*,int) ; 
 int set_string (void*,TYPE_2__ const*,char const*,void*) ; 
 int set_string_binary (void*,TYPE_2__ const*,char const*,void*) ; 
 int set_string_bool (void*,TYPE_2__ const*,char const*,void*) ; 
 int set_string_color (void*,TYPE_2__ const*,char const*,void*) ; 
 int set_string_image_size (void*,TYPE_2__ const*,char const*,void*) ; 
 int set_string_number (void*,void*,TYPE_2__ const*,char const*,void*) ; 
 int set_string_pixel_fmt (void*,TYPE_2__ const*,char const*,void*) ; 
 int set_string_sample_fmt (void*,TYPE_2__ const*,char const*,void*) ; 
 int set_string_video_rate (void*,TYPE_2__ const*,char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int write_number (void*,TYPE_2__ const*,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int av_opt_set(void *obj, const char *name, const char *val, int search_flags)
{
    int ret = 0;
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    if (!o || !target_obj)
        return AVERROR_OPTION_NOT_FOUND;
    if (!val && (o->type != AV_OPT_TYPE_STRING &&
                 o->type != AV_OPT_TYPE_PIXEL_FMT && o->type != AV_OPT_TYPE_SAMPLE_FMT &&
                 o->type != AV_OPT_TYPE_IMAGE_SIZE && o->type != AV_OPT_TYPE_VIDEO_RATE &&
                 o->type != AV_OPT_TYPE_DURATION && o->type != AV_OPT_TYPE_COLOR &&
                 o->type != AV_OPT_TYPE_CHANNEL_LAYOUT && o->type != AV_OPT_TYPE_BOOL))
        return AVERROR(EINVAL);

    if (o->flags & AV_OPT_FLAG_READONLY)
        return AVERROR(EINVAL);

    if (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = ((uint8_t *)target_obj) + o->offset;
    switch (o->type) {
    case AV_OPT_TYPE_BOOL:
        return set_string_bool(obj, o, val, dst);
    case AV_OPT_TYPE_STRING:
        return set_string(obj, o, val, dst);
    case AV_OPT_TYPE_BINARY:
        return set_string_binary(obj, o, val, dst);
    case AV_OPT_TYPE_FLAGS:
    case AV_OPT_TYPE_INT:
    case AV_OPT_TYPE_INT64:
    case AV_OPT_TYPE_UINT64:
    case AV_OPT_TYPE_FLOAT:
    case AV_OPT_TYPE_DOUBLE:
    case AV_OPT_TYPE_RATIONAL:
        return set_string_number(obj, target_obj, o, val, dst);
    case AV_OPT_TYPE_IMAGE_SIZE:
        return set_string_image_size(obj, o, val, dst);
    case AV_OPT_TYPE_VIDEO_RATE: {
        AVRational tmp;
        ret = set_string_video_rate(obj, o, val, &tmp);
        if (ret < 0)
            return ret;
        return write_number(obj, o, dst, 1, tmp.den, tmp.num);
    }
    case AV_OPT_TYPE_PIXEL_FMT:
        return set_string_pixel_fmt(obj, o, val, dst);
    case AV_OPT_TYPE_SAMPLE_FMT:
        return set_string_sample_fmt(obj, o, val, dst);
    case AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            if (val) {
                if ((ret = av_parse_time(&usecs, val, 1)) < 0) {
                    av_log(obj, AV_LOG_ERROR, "Unable to parse option value \"%s\" as duration\n", val);
                    return ret;
                }
            }
            if (usecs < o->min || usecs > o->max) {
                av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                return AVERROR(ERANGE);
            }
            *(int64_t *)dst = usecs;
            return 0;
        }
    case AV_OPT_TYPE_COLOR:
        return set_string_color(obj, o, val, dst);
    case AV_OPT_TYPE_CHANNEL_LAYOUT:
        if (!val || !strcmp(val, "none")) {
            *(int64_t *)dst = 0;
        } else {
            int64_t cl = av_get_channel_layout(val);
            if (!cl) {
                av_log(obj, AV_LOG_ERROR, "Unable to parse option value \"%s\" as channel layout\n", val);
                ret = AVERROR(EINVAL);
            }
            *(int64_t *)dst = cl;
            return ret;
        }
        break;
    }

    av_log(obj, AV_LOG_ERROR, "Invalid option type.\n");
    return AVERROR(EINVAL);
}