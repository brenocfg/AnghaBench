#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  list_audio; } ;
typedef  TYPE_2__ hb_title_t ;
struct TYPE_6__ {char* iso639_2; } ;
struct TYPE_8__ {TYPE_1__ lang; } ;
typedef  TYPE_3__ hb_audio_config_t ;
typedef  scalar_t__ gint ;
typedef  char gchar ;

/* Variables and functions */
 int /*<<< orphan*/  g_debug (char*) ; 
 TYPE_3__* hb_list_audio_config_item (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ hb_list_count (int /*<<< orphan*/ ) ; 

const gchar*
ghb_get_source_audio_lang(const hb_title_t *title, gint track)
{
    hb_audio_config_t * audio;
    const gchar *lang = "und";

    g_debug("ghb_lookup_1st_audio_lang ()\n");
    if (title == NULL)
        return lang;
    if (hb_list_count( title->list_audio ) <= track)
        return lang;

    audio = hb_list_audio_config_item(title->list_audio, track);
    if (audio == NULL)
        return lang;

    lang = audio->lang.iso639_2;
    return lang;
}