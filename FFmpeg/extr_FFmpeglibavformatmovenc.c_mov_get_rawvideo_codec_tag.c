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
struct TYPE_8__ {scalar_t__ pix_fmt; int tag; int /*<<< orphan*/  bps; } ;
struct TYPE_7__ {TYPE_1__* par; } ;
struct TYPE_6__ {int codec_tag; scalar_t__ format; int /*<<< orphan*/  bits_per_coded_sample; } ;
typedef  TYPE_2__ MOVTrack ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PIX_FMT_GRAY8 ; 
 scalar_t__ AV_PIX_FMT_NONE ; 
 int FF_ARRAY_ELEMS (TYPE_3__*) ; 
 int MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  av_get_pix_fmt_name (scalar_t__) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int avpriv_find_pix_fmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avpriv_pix_fmt_bps_mov ; 
 TYPE_3__* mov_pix_fmt_tags ; 

__attribute__((used)) static int mov_get_rawvideo_codec_tag(AVFormatContext *s, MOVTrack *track)
{
    int tag = track->par->codec_tag;
    int i;
    enum AVPixelFormat pix_fmt;

    for (i = 0; i < FF_ARRAY_ELEMS(mov_pix_fmt_tags); i++) {
        if (track->par->format == mov_pix_fmt_tags[i].pix_fmt) {
            tag = mov_pix_fmt_tags[i].tag;
            track->par->bits_per_coded_sample = mov_pix_fmt_tags[i].bps;
            if (track->par->codec_tag == mov_pix_fmt_tags[i].tag)
                break;
        }
    }

    pix_fmt = avpriv_find_pix_fmt(avpriv_pix_fmt_bps_mov,
                                  track->par->bits_per_coded_sample);
    if (tag == MKTAG('r','a','w',' ') &&
        track->par->format != pix_fmt &&
        track->par->format != AV_PIX_FMT_GRAY8 &&
        track->par->format != AV_PIX_FMT_NONE)
        av_log(s, AV_LOG_ERROR, "%s rawvideo cannot be written to mov, output file will be unreadable\n",
               av_get_pix_fmt_name(track->par->format));
    return tag;
}