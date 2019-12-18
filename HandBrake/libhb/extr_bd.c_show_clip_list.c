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
typedef  int int64_t ;
struct TYPE_5__ {int out_time; int in_time; int /*<<< orphan*/  clip_id; } ;
struct TYPE_4__ {int clip_count; TYPE_2__* clips; } ;
typedef  TYPE_1__ BLURAY_TITLE_INFO ;
typedef  TYPE_2__ BLURAY_CLIP_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  hb_log (char*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void show_clip_list( BLURAY_TITLE_INFO * ti )
{
    int ii;

    for (ii = 0; ii < ti->clip_count; ii++)
    {
        BLURAY_CLIP_INFO * ci = &ti->clips[ii];
        int64_t            duration = ci->out_time - ci->in_time;
        int                hh, mm, ss;

        hh = duration / (90000 * 60 * 60);
        mm = (duration / (90000 * 60)) % 60;
        ss = (duration / 90000) % 60;
        hb_log("bd:\t\t%s.M2TS -- Duration: %02d:%02d:%02d",
               ti->clips[ii].clip_id, hh, mm, ss);
    }
}