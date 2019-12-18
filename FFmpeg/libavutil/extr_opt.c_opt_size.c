#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
typedef  enum AVOptionType { ____Placeholder_AVOptionType } AVOptionType ;
typedef  int /*<<< orphan*/  AVRational ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
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

__attribute__((used)) static int opt_size(enum AVOptionType type)
{
    switch(type) {
    case AV_OPT_TYPE_BOOL:
    case AV_OPT_TYPE_INT:
    case AV_OPT_TYPE_FLAGS:
        return sizeof(int);
    case AV_OPT_TYPE_DURATION:
    case AV_OPT_TYPE_CHANNEL_LAYOUT:
    case AV_OPT_TYPE_INT64:
    case AV_OPT_TYPE_UINT64:
        return sizeof(int64_t);
    case AV_OPT_TYPE_DOUBLE:
        return sizeof(double);
    case AV_OPT_TYPE_FLOAT:
        return sizeof(float);
    case AV_OPT_TYPE_STRING:
        return sizeof(uint8_t*);
    case AV_OPT_TYPE_VIDEO_RATE:
    case AV_OPT_TYPE_RATIONAL:
        return sizeof(AVRational);
    case AV_OPT_TYPE_BINARY:
        return sizeof(uint8_t*) + sizeof(int);
    case AV_OPT_TYPE_IMAGE_SIZE:
        return sizeof(int[2]);
    case AV_OPT_TYPE_PIXEL_FMT:
        return sizeof(enum AVPixelFormat);
    case AV_OPT_TYPE_SAMPLE_FMT:
        return sizeof(enum AVSampleFormat);
    case AV_OPT_TYPE_COLOR:
        return 4;
    }
    return AVERROR(EINVAL);
}