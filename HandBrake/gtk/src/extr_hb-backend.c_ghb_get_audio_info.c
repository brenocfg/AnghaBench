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
struct TYPE_3__ {int /*<<< orphan*/  list_audio; } ;
typedef  TYPE_1__ hb_title_t ;
typedef  int /*<<< orphan*/  hb_audio_config_t ;
typedef  int /*<<< orphan*/  gint ;

/* Variables and functions */
 int /*<<< orphan*/ * hb_list_audio_config_item (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_list_count (int /*<<< orphan*/ ) ; 

hb_audio_config_t*
ghb_get_audio_info(const hb_title_t *title, gint track)
{
    if (title == NULL) return NULL;
    if (!hb_list_count(title->list_audio))
    {
        return NULL;
    }
    return hb_list_audio_config_item(title->list_audio, track);
}