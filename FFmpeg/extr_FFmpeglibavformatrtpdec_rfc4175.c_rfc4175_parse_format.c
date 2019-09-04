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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_8__ {TYPE_1__* codecpar; } ;
struct TYPE_7__ {int xinc; int depth; int pgroup; int frame_size; int width; int height; int /*<<< orphan*/  sampling; } ;
struct TYPE_6__ {int format; int codec_tag; int bits_per_coded_sample; } ;
typedef  TYPE_2__ PayloadContext ;
typedef  TYPE_3__ AVStream ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_PIX_FMT_NONE ; 
 int AV_PIX_FMT_UYVY422 ; 
 int AV_PIX_FMT_YUV422P10 ; 
 int MKTAG (unsigned char,char,char,char) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int rfc4175_parse_format(AVStream *stream, PayloadContext *data)
{
    enum AVPixelFormat pixfmt = AV_PIX_FMT_NONE;
    int bits_per_sample = 0;
    int tag = 0;

    if (!strncmp(data->sampling, "YCbCr-4:2:2", 11)) {
        tag = MKTAG('U', 'Y', 'V', 'Y');
        data->xinc = 2;

        if (data->depth == 8) {
            data->pgroup = 4;
            bits_per_sample = 16;
            pixfmt = AV_PIX_FMT_UYVY422;
        } else if (data->depth == 10) {
            data->pgroup = 5;
            bits_per_sample = 20;
            pixfmt = AV_PIX_FMT_YUV422P10;
        } else {
            return AVERROR_INVALIDDATA;
        }
    } else {
        return AVERROR_INVALIDDATA;
    }

    stream->codecpar->format = pixfmt;
    stream->codecpar->codec_tag = tag;
    stream->codecpar->bits_per_coded_sample = bits_per_sample;
    data->frame_size = data->width * data->height * data->pgroup / data->xinc;

    return 0;
}