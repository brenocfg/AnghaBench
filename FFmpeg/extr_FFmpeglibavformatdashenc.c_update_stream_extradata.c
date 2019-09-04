#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_13__ {scalar_t__ extradata_size; int /*<<< orphan*/  extradata; } ;
struct TYPE_12__ {int /*<<< orphan*/  codec_str; TYPE_3__* ctx; } ;
struct TYPE_11__ {TYPE_2__** streams; } ;
struct TYPE_10__ {TYPE_1__* codecpar; } ;
struct TYPE_9__ {scalar_t__ extradata_size; int /*<<< orphan*/ * extradata; } ;
typedef  TYPE_4__ OutputStream ;
typedef  int /*<<< orphan*/  AVRational ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  TYPE_5__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * av_malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_codec_str (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int update_stream_extradata(AVFormatContext *s, OutputStream *os,
                                   AVCodecParameters *par,
                                   AVRational *frame_rate)
{
    uint8_t *extradata;

    if (os->ctx->streams[0]->codecpar->extradata_size || !par->extradata_size)
        return 0;

    extradata = av_malloc(par->extradata_size);

    if (!extradata)
        return AVERROR(ENOMEM);

    memcpy(extradata, par->extradata, par->extradata_size);

    os->ctx->streams[0]->codecpar->extradata = extradata;
    os->ctx->streams[0]->codecpar->extradata_size = par->extradata_size;

    set_codec_str(s, par, frame_rate, os->codec_str, sizeof(os->codec_str));

    return 0;
}