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
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ghb_dict_get_bool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * hb_preset_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static gboolean
preset_is_folder(hb_preset_index_t *path)
{
    GhbValue *dict;
    gboolean folder = FALSE;

    dict = hb_preset_get(path);
    if (dict)
    {
        folder = ghb_dict_get_bool(dict, "Folder");
    }
    return folder;
}