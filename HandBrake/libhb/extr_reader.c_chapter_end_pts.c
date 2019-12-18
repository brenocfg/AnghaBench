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
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {int /*<<< orphan*/  list_chapter; } ;
typedef  TYPE_1__ hb_title_t ;
struct TYPE_6__ {scalar_t__ duration; } ;
typedef  TYPE_2__ hb_chapter_t ;

/* Variables and functions */
 TYPE_2__* hb_list_item (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int64_t chapter_end_pts(hb_title_t * title, int chapter_end )
{
    hb_chapter_t * chapter;
    int64_t        duration;
    int            ii;

    duration = 0;
    for (ii = 0; ii < chapter_end; ii++)
    {
        chapter = hb_list_item(title->list_chapter, ii);
        duration += chapter->duration;
    }
    return duration;
}