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
typedef  int /*<<< orphan*/  hb_value_t ;
typedef  int /*<<< orphan*/  hb_preset_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_preset_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * preset_lookup_path (char const*,int,int) ; 

hb_value_t * hb_preset_search(const char *name, int recurse, int type)
{
    hb_preset_index_t *path = preset_lookup_path(name, recurse, type);
    hb_value_t *preset = hb_preset_get(path);
    free(path);
    return preset;
}