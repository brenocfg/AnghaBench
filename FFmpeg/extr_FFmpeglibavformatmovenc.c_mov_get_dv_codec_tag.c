#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* st; TYPE_1__* par; } ;
struct TYPE_7__ {int den; } ;
struct TYPE_8__ {TYPE_2__ time_base; } ;
struct TYPE_6__ {int width; int height; scalar_t__ format; } ;
typedef  TYPE_4__ MOVTrack ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PIX_FMT_YUV420P ; 
 scalar_t__ AV_PIX_FMT_YUV422P ; 
 int MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mov_get_dv_codec_tag(AVFormatContext *s, MOVTrack *track)
{
    int tag;

    if (track->par->width == 720) { /* SD */
        if (track->par->height == 480) { /* NTSC */
            if  (track->par->format == AV_PIX_FMT_YUV422P) tag = MKTAG('d','v','5','n');
            else                                            tag = MKTAG('d','v','c',' ');
       }else if (track->par->format == AV_PIX_FMT_YUV422P) tag = MKTAG('d','v','5','p');
        else if (track->par->format == AV_PIX_FMT_YUV420P) tag = MKTAG('d','v','c','p');
        else                                                tag = MKTAG('d','v','p','p');
    } else if (track->par->height == 720) { /* HD 720 line */
        if  (track->st->time_base.den == 50)                tag = MKTAG('d','v','h','q');
        else                                                tag = MKTAG('d','v','h','p');
    } else if (track->par->height == 1080) { /* HD 1080 line */
        if  (track->st->time_base.den == 25)                tag = MKTAG('d','v','h','5');
        else                                                tag = MKTAG('d','v','h','6');
    } else {
        av_log(s, AV_LOG_ERROR, "unsupported height for dv codec\n");
        return 0;
    }

    return tag;
}