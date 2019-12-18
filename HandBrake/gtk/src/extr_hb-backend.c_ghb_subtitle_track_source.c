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
struct TYPE_5__ {int /*<<< orphan*/  list_subtitle; } ;
typedef  TYPE_1__ hb_title_t ;
struct TYPE_6__ {int source; } ;
typedef  TYPE_2__ hb_subtitle_t ;
typedef  int gint ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int IMPORTSRT ; 
 int VOBSUB ; 
 int ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* ghb_lookup_title (int,int*) ; 
 TYPE_2__* hb_list_item (int /*<<< orphan*/ ,int) ; 

gint
ghb_subtitle_track_source(GhbValue *settings, gint track)
{
    gint title_id, titleindex;
    const hb_title_t *title;

    if (track == -2)
        return IMPORTSRT;
    if (track < 0)
        return VOBSUB;
    title_id = ghb_dict_get_int(settings, "title");
    title = ghb_lookup_title(title_id, &titleindex);
    if (title == NULL)
        return VOBSUB;

    hb_subtitle_t * sub;
    sub = hb_list_item( title->list_subtitle, track);
    if (sub != NULL)
        return sub->source;
    else
        return VOBSUB;
}