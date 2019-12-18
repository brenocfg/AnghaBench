#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int* crop; TYPE_2__* title; } ;
typedef  TYPE_3__ hb_job_t ;
struct TYPE_12__ {int /*<<< orphan*/  subtitle; } ;
typedef  TYPE_4__ hb_filter_object_t ;
struct TYPE_9__ {int height; int width; } ;
struct TYPE_10__ {TYPE_1__ geometry; } ;

/* Variables and functions */
 int /*<<< orphan*/  HB_FONT_SANS ; 
 int /*<<< orphan*/  hb_subtitle_add_ssa_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,int,int) ; 
 int ssa_post_init (TYPE_4__*,TYPE_3__*) ; 

__attribute__((used)) static int textsub_post_init( hb_filter_object_t * filter, hb_job_t * job )
{
    // Text subtitles for which we create a dummy ASS header need
    // to have the header rewritten with the correct dimensions.
    int height = job->title->geometry.height - job->crop[0] - job->crop[1];
    int width = job->title->geometry.width - job->crop[2] - job->crop[3];
    hb_subtitle_add_ssa_header(filter->subtitle, HB_FONT_SANS,
                               .066 * job->title->geometry.height,
                               width, height);
    return ssa_post_init(filter, job);
}