#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* codecpar; } ;
struct TYPE_5__ {scalar_t__ codec_type; } ;
typedef  TYPE_2__ AVStream ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ is_cover_image (TYPE_2__ const*) ; 

__attribute__((used)) static int rtp_hinting_needed(const AVStream *st)
{
    /* Add hint tracks for each real audio and video stream */
    if (is_cover_image(st))
        return 0;
    return st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO ||
           st->codecpar->codec_type == AVMEDIA_TYPE_AUDIO;
}