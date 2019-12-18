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
typedef  int /*<<< orphan*/  preset_do_context_t ;
typedef  int /*<<< orphan*/  hb_value_t ;

/* Variables and functions */
 scalar_t__ HB_PRESET_TYPE_OFFICIAL ; 
 int PRESET_DO_DELETE ; 
 int PRESET_DO_NEXT ; 
 int /*<<< orphan*/  hb_dict_get (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ hb_value_get_int (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_delete_builtin(hb_value_t *preset, preset_do_context_t *ctx)
{
    if (hb_value_get_int(hb_dict_get(preset, "Type")) == HB_PRESET_TYPE_OFFICIAL)
        return PRESET_DO_DELETE;
    return PRESET_DO_NEXT;
}