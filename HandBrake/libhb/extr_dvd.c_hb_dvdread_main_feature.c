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
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {scalar_t__ duration; int index; } ;
typedef  TYPE_1__ hb_title_t ;
typedef  int /*<<< orphan*/  hb_list_t ;
typedef  int /*<<< orphan*/  hb_dvd_t ;

/* Variables and functions */
 int hb_list_count (int /*<<< orphan*/ *) ; 
 TYPE_1__* hb_list_item (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hb_dvdread_main_feature( hb_dvd_t * e, hb_list_t * list_title )
{
    int ii;
    uint64_t longest_duration = 0;
    int longest = -1;

    for ( ii = 0; ii < hb_list_count( list_title ); ii++ )
    {
        hb_title_t * title = hb_list_item( list_title, ii );
        if ( title->duration > longest_duration )
        {
            longest_duration = title->duration;
            longest = title->index;
        }
    }
    return longest;
}