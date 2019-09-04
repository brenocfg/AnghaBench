#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_13__ {int i64; double dbl; int /*<<< orphan*/  str; } ;
struct TYPE_15__ {int offset; int flags; int type; int /*<<< orphan*/  name; TYPE_1__ default_val; } ;
struct TYPE_14__ {int den; int num; } ;
typedef  TYPE_2__ AVRational ;
typedef  TYPE_3__ AVOption ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int AV_OPT_FLAG_READONLY ; 
#define  AV_OPT_TYPE_BINARY 146 
#define  AV_OPT_TYPE_BOOL 145 
#define  AV_OPT_TYPE_CHANNEL_LAYOUT 144 
#define  AV_OPT_TYPE_COLOR 143 
#define  AV_OPT_TYPE_CONST 142 
#define  AV_OPT_TYPE_DICT 141 
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
 int /*<<< orphan*/  INT_MAX ; 
 TYPE_2__ av_d2q (double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* av_opt_next (void*,TYPE_3__ const*) ; 
 int /*<<< orphan*/  set_string (void*,TYPE_3__ const*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  set_string_binary (void*,TYPE_3__ const*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  set_string_color (void*,TYPE_3__ const*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  set_string_image_size (void*,TYPE_3__ const*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  set_string_video_rate (void*,TYPE_3__ const*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  write_number (void*,TYPE_3__ const*,void*,int,int,int) ; 

void av_opt_set_defaults2(void *s, int mask, int flags)
{
    const AVOption *opt = NULL;
    while ((opt = av_opt_next(s, opt))) {
        void *dst = ((uint8_t*)s) + opt->offset;

        if ((opt->flags & mask) != flags)
            continue;

        if (opt->flags & AV_OPT_FLAG_READONLY)
            continue;

        switch (opt->type) {
            case AV_OPT_TYPE_CONST:
                /* Nothing to be done here */
                break;
            case AV_OPT_TYPE_BOOL:
            case AV_OPT_TYPE_FLAGS:
            case AV_OPT_TYPE_INT:
            case AV_OPT_TYPE_INT64:
            case AV_OPT_TYPE_UINT64:
            case AV_OPT_TYPE_DURATION:
            case AV_OPT_TYPE_CHANNEL_LAYOUT:
            case AV_OPT_TYPE_PIXEL_FMT:
            case AV_OPT_TYPE_SAMPLE_FMT:
                write_number(s, opt, dst, 1, 1, opt->default_val.i64);
                break;
            case AV_OPT_TYPE_DOUBLE:
            case AV_OPT_TYPE_FLOAT: {
                double val;
                val = opt->default_val.dbl;
                write_number(s, opt, dst, val, 1, 1);
            }
            break;
            case AV_OPT_TYPE_RATIONAL: {
                AVRational val;
                val = av_d2q(opt->default_val.dbl, INT_MAX);
                write_number(s, opt, dst, 1, val.den, val.num);
            }
            break;
            case AV_OPT_TYPE_COLOR:
                set_string_color(s, opt, opt->default_val.str, dst);
                break;
            case AV_OPT_TYPE_STRING:
                set_string(s, opt, opt->default_val.str, dst);
                break;
            case AV_OPT_TYPE_IMAGE_SIZE:
                set_string_image_size(s, opt, opt->default_val.str, dst);
                break;
            case AV_OPT_TYPE_VIDEO_RATE:
                set_string_video_rate(s, opt, opt->default_val.str, dst);
                break;
            case AV_OPT_TYPE_BINARY:
                set_string_binary(s, opt, opt->default_val.str, dst);
                break;
            case AV_OPT_TYPE_DICT:
                /* Cannot set defaults for these types */
            break;
        default:
            av_log(s, AV_LOG_DEBUG, "AVOption type %d of option %s not implemented yet\n",
                   opt->type, opt->name);
        }
    }
}