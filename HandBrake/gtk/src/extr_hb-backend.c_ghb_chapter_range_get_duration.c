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
struct TYPE_5__ {int /*<<< orphan*/  list_chapter; scalar_t__ duration; } ;
typedef  TYPE_1__ hb_title_t ;
struct TYPE_6__ {scalar_t__ duration; } ;
typedef  TYPE_2__ hb_chapter_t ;
typedef  scalar_t__ gint64 ;
typedef  scalar_t__ gint ;

/* Variables and functions */
 scalar_t__ hb_list_count (int /*<<< orphan*/ ) ; 
 TYPE_2__* hb_list_item (int /*<<< orphan*/ ,scalar_t__) ; 

gint64
ghb_chapter_range_get_duration(const hb_title_t *title, gint sc, gint ec)
{
    hb_chapter_t * chapter;
    gint count, c;
    gint64 duration;

    if (title == NULL) return 0;

    duration = title->duration;

    count = hb_list_count(title->list_chapter);
    if (sc > count) sc = count;
    if (ec > count) ec = count;

    if (sc == 1 && ec == count)
        return duration;

    duration = 0;
    for (c = sc; c <= ec; c++)
    {
        chapter = hb_list_item(title->list_chapter, c-1);
        duration += chapter->duration;
    }
    return duration;
}