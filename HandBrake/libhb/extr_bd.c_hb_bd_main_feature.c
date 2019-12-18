#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  double uint64_t ;
struct TYPE_9__ {int index; double duration; } ;
typedef  TYPE_2__ hb_title_t ;
typedef  int /*<<< orphan*/  hb_list_t ;
struct TYPE_10__ {TYPE_4__** title_info; } ;
typedef  TYPE_3__ hb_bd_t ;
struct TYPE_12__ {int format; } ;
struct TYPE_11__ {int chapter_count; TYPE_1__* clips; } ;
struct TYPE_8__ {TYPE_5__* video_streams; } ;
typedef  TYPE_4__ BLURAY_TITLE_INFO ;
typedef  TYPE_5__ BLURAY_STREAM_INFO ;

/* Variables and functions */
 int hb_list_count (int /*<<< orphan*/ *) ; 
 TYPE_2__* hb_list_item (int /*<<< orphan*/ *,int) ; 

int hb_bd_main_feature( hb_bd_t * d, hb_list_t * list_title )
{
    int longest = 0;
    int ii;
    uint64_t longest_duration = 0;
    int highest_rank = 0;
    int most_chapters = 0;
    int rank[8] = {0, 1, 3, 2, 6, 5, 7, 4};
    BLURAY_TITLE_INFO * ti;

    for ( ii = 0; ii < hb_list_count( list_title ); ii++ )
    {
        hb_title_t * title = hb_list_item( list_title, ii );
        ti = d->title_info[title->index - 1];
        if ( ti )
        {
            BLURAY_STREAM_INFO * bdvideo = &ti->clips[0].video_streams[0];
            if ( title->duration > longest_duration * 0.7 && bdvideo->format < 8 )
            {
                if (highest_rank < rank[bdvideo->format] ||
                    ( title->duration > longest_duration &&
                          highest_rank == rank[bdvideo->format]))
                {
                    longest = title->index;
                    longest_duration = title->duration;
                    highest_rank = rank[bdvideo->format];
                    most_chapters = ti->chapter_count;
                }
                else if (highest_rank == rank[bdvideo->format] &&
                         title->duration == longest_duration &&
                         ti->chapter_count > most_chapters)
                {
                    longest = title->index;
                    most_chapters = ti->chapter_count;
                }
            }
        }
        else if ( title->duration > longest_duration )
        {
            longest_duration = title->duration;
            longest = title->index;
        }
    }
    return longest;
}