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

/* Variables and functions */
 int /*<<< orphan*/ * hb_presets_get () ; 
 char* hb_value_get_json (int /*<<< orphan*/ *) ; 

char * hb_presets_get_json(void)
{
    char * result;
    hb_value_t *presets = hb_presets_get();
    result = hb_value_get_json(presets);
    return result;
}