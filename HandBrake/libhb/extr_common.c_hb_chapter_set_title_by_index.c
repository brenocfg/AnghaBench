#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  list_chapter; } ;
typedef  TYPE_1__ hb_job_t ;
typedef  int /*<<< orphan*/  hb_chapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_chapter_set_title (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * hb_list_item (int /*<<< orphan*/ ,int) ; 

void hb_chapter_set_title_by_index( hb_job_t * job, int chapter_index, const char * title )
{
    hb_chapter_t * chapter = hb_list_item( job->list_chapter, chapter_index - 1 );
    hb_chapter_set_title( chapter, title );
}