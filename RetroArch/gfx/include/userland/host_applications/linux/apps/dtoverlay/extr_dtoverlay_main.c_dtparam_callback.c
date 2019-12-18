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
struct dtparam_state {int /*<<< orphan*/  used_props; scalar_t__ override_value; } ;
typedef  int /*<<< orphan*/  prop_id ;
typedef  int /*<<< orphan*/  DTBLOB_T ;

/* Variables and functions */
 int FDT_ERR_INTERNAL ; 
 int dtoverlay_override_one_target (int,int /*<<< orphan*/ *,int,char const*,int,int,int,void*) ; 
 scalar_t__ snprintf (char*,int,char*,int,char const*) ; 
 int /*<<< orphan*/  string_vec_add (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ string_vec_find (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int dtparam_callback(int override_type,
		     DTBLOB_T *dtb, int node_off,
		     const char *prop_name, int target_phandle,
		     int target_off, int target_size,
		     void *callback_value)
{
    struct dtparam_state *state = callback_value;
    char prop_id[80];
    int err;

    err = dtoverlay_override_one_target(override_type,
					dtb, node_off,
					prop_name, target_phandle,
					target_off, target_size,
					(void *)state->override_value);

    if ((err == 0) && (target_phandle != 0))
    {
	if (snprintf(prop_id, sizeof(prop_id), "%08x%s", target_phandle,
		     prop_name) < 0)
	    err = FDT_ERR_INTERNAL;
	else if (string_vec_find(state->used_props, prop_id, 0) < 0)
	    string_vec_add(state->used_props, prop_id, 0);
    }

    return err;
}