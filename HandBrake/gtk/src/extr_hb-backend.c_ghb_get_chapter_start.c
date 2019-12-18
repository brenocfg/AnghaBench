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
struct TYPE_5__ {int /*<<< orphan*/  list_chapter; } ;
typedef  TYPE_1__ hb_title_t ;
struct TYPE_6__ {scalar_t__ duration; } ;
typedef  TYPE_2__ hb_chapter_t ;
typedef  scalar_t__ gint64 ;
typedef  scalar_t__ gint ;

/* Variables and functions */
 scalar_t__ hb_list_count (int /*<<< orphan*/ ) ; 
 TYPE_2__* hb_list_item (int /*<<< orphan*/ ,scalar_t__) ; 

gint64
ghb_get_chapter_start(const hb_title_t *title, gint chap)
{
    hb_chapter_t * chapter;
    gint count, ii;
    gint64 start = 0;

    if (title == NULL) return 0;
    count = hb_list_count( title->list_chapter );
    if (chap > count) return chap = count;
    for (ii = 0; ii < chap; ii++)
    {
        chapter = hb_list_item(title->list_chapter, ii);
        start += chapter->duration;
    }
    return start;
}