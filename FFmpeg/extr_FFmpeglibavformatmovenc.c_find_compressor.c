#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  value; } ;
struct TYPE_10__ {int /*<<< orphan*/  metadata; } ;
struct TYPE_9__ {scalar_t__ mode; TYPE_1__* par; TYPE_3__* st; } ;
struct TYPE_8__ {int width; int height; scalar_t__ codec_id; scalar_t__ field_order; scalar_t__ format; } ;
typedef  TYPE_2__ MOVTrack ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVDictionaryEntry ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_MPEG2VIDEO ; 
 scalar_t__ AV_FIELD_PROGRESSIVE ; 
 scalar_t__ AV_PIX_FMT_YUV422P ; 
 scalar_t__ MODE_MOV ; 
 TYPE_4__* av_dict_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_strlcatf (char*,int,char*,...) ; 
 int /*<<< orphan*/  av_strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int defined_frame_rate (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static void find_compressor(char * compressor_name, int len, MOVTrack *track)
{
    AVDictionaryEntry *encoder;
    int xdcam_res =  (track->par->width == 1280 && track->par->height == 720)
                  || (track->par->width == 1440 && track->par->height == 1080)
                  || (track->par->width == 1920 && track->par->height == 1080);

    if (track->mode == MODE_MOV &&
        (encoder = av_dict_get(track->st->metadata, "encoder", NULL, 0))) {
        av_strlcpy(compressor_name, encoder->value, 32);
    } else if (track->par->codec_id == AV_CODEC_ID_MPEG2VIDEO && xdcam_res) {
        int interlaced = track->par->field_order > AV_FIELD_PROGRESSIVE;
        AVStream *st = track->st;
        int rate = defined_frame_rate(NULL, st);
        av_strlcatf(compressor_name, len, "XDCAM");
        if (track->par->format == AV_PIX_FMT_YUV422P) {
            av_strlcatf(compressor_name, len, " HD422");
        } else if(track->par->width == 1440) {
            av_strlcatf(compressor_name, len, " HD");
        } else
            av_strlcatf(compressor_name, len, " EX");

        av_strlcatf(compressor_name, len, " %d%c", track->par->height, interlaced ? 'i' : 'p');

        av_strlcatf(compressor_name, len, "%d", rate * (interlaced + 1));
    }
}