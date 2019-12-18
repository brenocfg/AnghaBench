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
typedef  int /*<<< orphan*/  hb_preset_index_t ;
typedef  int /*<<< orphan*/  gint ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  g_warning (char*) ; 
 int /*<<< orphan*/  ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * hb_preset_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static gint
preset_get_type(hb_preset_index_t *path)
{
    GhbValue *dict;
    dict = hb_preset_get(path);
    if (dict)
    {
        return ghb_dict_get_int(dict, "Type");
    }
    else
    {
        g_warning("ghb_preset_get_type (): internal preset lookup error");
        return 0;
    }
    return 0;
}