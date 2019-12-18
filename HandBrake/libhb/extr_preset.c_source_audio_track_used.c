#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * hb_dict_init () ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static hb_dict_t * source_audio_track_used(hb_dict_t *track_dict, int track)
{
    // Kind of hacky, but keys must be strings
    char key[8];
    snprintf(key, sizeof(key), "%d", track);

    hb_dict_t *used = hb_dict_get(track_dict, key);
    if (used == NULL)
    {
        used = hb_dict_init();
        hb_dict_set(track_dict, key, used);
    }
    return used;
}