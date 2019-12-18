#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* par; int /*<<< orphan*/ * st; } ;
struct TYPE_4__ {int codec_tag; scalar_t__ field_order; scalar_t__ format; int width; int height; } ;
typedef  TYPE_2__ MOVTrack ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 scalar_t__ AV_FIELD_PROGRESSIVE ; 
 scalar_t__ AV_PIX_FMT_YUV420P ; 
 scalar_t__ AV_PIX_FMT_YUV422P ; 
 int MKTAG (char,char,char,char) ; 
 int defined_frame_rate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mov_get_mpeg2_xdcam_codec_tag(AVFormatContext *s, MOVTrack *track)
{
    int tag = track->par->codec_tag;
    int interlaced = track->par->field_order > AV_FIELD_PROGRESSIVE;
    AVStream *st = track->st;
    int rate = defined_frame_rate(s, st);

    if (!tag)
        tag = MKTAG('m', '2', 'v', '1'); //fallback tag

    if (track->par->format == AV_PIX_FMT_YUV420P) {
        if (track->par->width == 1280 && track->par->height == 720) {
            if (!interlaced) {
                if      (rate == 24) tag = MKTAG('x','d','v','4');
                else if (rate == 25) tag = MKTAG('x','d','v','5');
                else if (rate == 30) tag = MKTAG('x','d','v','1');
                else if (rate == 50) tag = MKTAG('x','d','v','a');
                else if (rate == 60) tag = MKTAG('x','d','v','9');
            }
        } else if (track->par->width == 1440 && track->par->height == 1080) {
            if (!interlaced) {
                if      (rate == 24) tag = MKTAG('x','d','v','6');
                else if (rate == 25) tag = MKTAG('x','d','v','7');
                else if (rate == 30) tag = MKTAG('x','d','v','8');
            } else {
                if      (rate == 25) tag = MKTAG('x','d','v','3');
                else if (rate == 30) tag = MKTAG('x','d','v','2');
            }
        } else if (track->par->width == 1920 && track->par->height == 1080) {
            if (!interlaced) {
                if      (rate == 24) tag = MKTAG('x','d','v','d');
                else if (rate == 25) tag = MKTAG('x','d','v','e');
                else if (rate == 30) tag = MKTAG('x','d','v','f');
            } else {
                if      (rate == 25) tag = MKTAG('x','d','v','c');
                else if (rate == 30) tag = MKTAG('x','d','v','b');
            }
        }
    } else if (track->par->format == AV_PIX_FMT_YUV422P) {
        if (track->par->width == 1280 && track->par->height == 720) {
            if (!interlaced) {
                if      (rate == 24) tag = MKTAG('x','d','5','4');
                else if (rate == 25) tag = MKTAG('x','d','5','5');
                else if (rate == 30) tag = MKTAG('x','d','5','1');
                else if (rate == 50) tag = MKTAG('x','d','5','a');
                else if (rate == 60) tag = MKTAG('x','d','5','9');
            }
        } else if (track->par->width == 1920 && track->par->height == 1080) {
            if (!interlaced) {
                if      (rate == 24) tag = MKTAG('x','d','5','d');
                else if (rate == 25) tag = MKTAG('x','d','5','e');
                else if (rate == 30) tag = MKTAG('x','d','5','f');
            } else {
                if      (rate == 25) tag = MKTAG('x','d','5','c');
                else if (rate == 30) tag = MKTAG('x','d','5','b');
            }
        }
    }

    return tag;
}