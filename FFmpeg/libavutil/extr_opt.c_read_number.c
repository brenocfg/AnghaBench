#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_5__ {double dbl; } ;
struct TYPE_7__ {int type; TYPE_1__ default_val; } ;
struct TYPE_6__ {int num; int den; } ;
typedef  TYPE_2__ AVRational ;
typedef  TYPE_3__ AVOption ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_OPT_TYPE_BOOL 140 
#define  AV_OPT_TYPE_CHANNEL_LAYOUT 139 
#define  AV_OPT_TYPE_CONST 138 
#define  AV_OPT_TYPE_DOUBLE 137 
#define  AV_OPT_TYPE_DURATION 136 
#define  AV_OPT_TYPE_FLAGS 135 
#define  AV_OPT_TYPE_FLOAT 134 
#define  AV_OPT_TYPE_INT 133 
#define  AV_OPT_TYPE_INT64 132 
#define  AV_OPT_TYPE_PIXEL_FMT 131 
#define  AV_OPT_TYPE_RATIONAL 130 
#define  AV_OPT_TYPE_SAMPLE_FMT 129 
#define  AV_OPT_TYPE_UINT64 128 
 int /*<<< orphan*/  EINVAL ; 

__attribute__((used)) static int read_number(const AVOption *o, const void *dst, double *num, int *den, int64_t *intnum)
{
    switch (o->type) {
    case AV_OPT_TYPE_FLAGS:
        *intnum = *(unsigned int*)dst;
        return 0;
    case AV_OPT_TYPE_PIXEL_FMT:
        *intnum = *(enum AVPixelFormat *)dst;
        return 0;
    case AV_OPT_TYPE_SAMPLE_FMT:
        *intnum = *(enum AVSampleFormat *)dst;
        return 0;
    case AV_OPT_TYPE_BOOL:
    case AV_OPT_TYPE_INT:
        *intnum = *(int *)dst;
        return 0;
    case AV_OPT_TYPE_CHANNEL_LAYOUT:
    case AV_OPT_TYPE_DURATION:
    case AV_OPT_TYPE_INT64:
    case AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        return 0;
    case AV_OPT_TYPE_FLOAT:
        *num = *(float *)dst;
        return 0;
    case AV_OPT_TYPE_DOUBLE:
        *num = *(double *)dst;
        return 0;
    case AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->num;
        *den    = ((AVRational *)dst)->den;
        return 0;
    case AV_OPT_TYPE_CONST:
        *num = o->default_val.dbl;
        return 0;
    }
    return AVERROR(EINVAL);
}