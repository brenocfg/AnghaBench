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
typedef  int /*<<< orphan*/  hb_value_array_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 int /*<<< orphan*/ * hb_dict_init () ; 
 int /*<<< orphan*/  hb_dict_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  hb_dict_set_int (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  hb_dict_set_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  hb_value_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_subtitle(hb_value_array_t *list, int track,
                         int make_default, int force, int burn,
                         const char * name)
{
    hb_dict_t *subtitle_dict = hb_dict_init();
    hb_dict_set_int(subtitle_dict, "Track", track);
    hb_dict_set_bool(subtitle_dict, "Default", make_default);
    hb_dict_set_bool(subtitle_dict, "Forced", force);
    hb_dict_set_bool(subtitle_dict, "Burn", burn);
    if (name != NULL && name[0] != 0)
    {
        hb_dict_set_string(subtitle_dict, "Name", name);
    }
    hb_value_array_append(list, subtitle_dict);
}