#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* oformat; int /*<<< orphan*/  url; } ;
struct TYPE_12__ {scalar_t__ mode; TYPE_2__* par; int /*<<< orphan*/  st; } ;
struct TYPE_11__ {int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_tag; } ;
struct TYPE_10__ {int /*<<< orphan*/  codec_tag; } ;
typedef  TYPE_3__ MOVTrack ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ MODE_IPOD ; 
 scalar_t__ MODE_MOV ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_match_ext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  codec_cover_image_tags ; 
 unsigned int ff_codec_get_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_cover_image (int /*<<< orphan*/ ) ; 
 unsigned int mov_get_codec_tag (TYPE_4__*,TYPE_3__*) ; 
 unsigned int validate_codec_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int mov_find_codec_tag(AVFormatContext *s, MOVTrack *track)
{
    if (is_cover_image(track->st))
        return ff_codec_get_tag(codec_cover_image_tags, track->par->codec_id);

    if (track->mode == MODE_IPOD)
        if (!av_match_ext(s->url, "m4a") &&
            !av_match_ext(s->url, "m4v") &&
            !av_match_ext(s->url, "m4b"))
            av_log(s, AV_LOG_WARNING, "Warning, extension is not .m4a nor .m4v "
                   "Quicktime/Ipod might not play the file\n");

    if (track->mode == MODE_MOV) {
        return mov_get_codec_tag(s, track);
    } else
        return validate_codec_tag(s->oformat->codec_tag, track->par->codec_tag,
                                  track->par->codec_id);
}