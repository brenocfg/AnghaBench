#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  list_subtitle; } ;
typedef  TYPE_1__ hb_title_t ;
struct TYPE_7__ {char const* iso639_2; } ;
typedef  TYPE_2__ hb_subtitle_t ;
typedef  int gint ;
typedef  char gchar ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 char const* ghb_get_user_audio_lang (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ghb_lookup_title (int,int*) ; 
 TYPE_2__* hb_list_item (int /*<<< orphan*/ ,int) ; 

const gchar*
ghb_subtitle_track_lang(GhbValue *settings, gint track)
{
    gint title_id, titleindex;
    const hb_title_t * title;

    title_id = ghb_dict_get_int(settings, "title");
    title = ghb_lookup_title(title_id, &titleindex);
    if (title == NULL)  // Bad titleindex
        goto fail;
    if (track == -1)
        return ghb_get_user_audio_lang(settings, title, 0);
    if (track < 0)
        goto fail;

    hb_subtitle_t * sub;
    sub = hb_list_item( title->list_subtitle, track);
    if (sub != NULL)
        return sub->iso639_2;

fail:
    return "und";
}