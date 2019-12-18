#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cfm_flags; int /*<<< orphan*/  cfm_search_path; int /*<<< orphan*/  cfm_opts; int /*<<< orphan*/  cfm_defaults; int /*<<< orphan*/  cfm_type; } ;
typedef  TYPE_1__ cf_map_t ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  search_path; int /*<<< orphan*/  map_options; int /*<<< orphan*/  map_defaults; int /*<<< orphan*/  map_type; } ;

/* Variables and functions */
 int CFM_BROWSABLE_DIRS ; 
 int CFM_BROWSABLE_DIRS_FULL ; 
 int CFM_MOUNT_TYPE_AUTOFS ; 
 int CFM_SELECTORS_IN_DEFAULTS ; 
 int CFM_SUN_MAP_SYNTAX ; 
 TYPE_3__ gopt ; 

__attribute__((used)) static void
init_cf_map(cf_map_t *cfm)
{
  if (!cfm)
    return;

  /*
   * Initialize a regular map's flags and other variables from the
   * global ones, so that they are applied to all maps.  Of course, each map
   * can then override the flags individually.
   *
   * NOTES:
   * (1): Will only work for maps that appear after [global].
   * (2): I'm assigning pointers directly from the global map.
   */

  /* initialize map_type from [global] */
  cfm->cfm_type = gopt.map_type;

  /* initialize map_defaults from [global] */
  cfm->cfm_defaults = gopt.map_defaults;

  /* initialize map_opts from [global] */
  cfm->cfm_opts = gopt.map_options;

  /* initialize search_path from [global] */
  cfm->cfm_search_path = gopt.search_path;

  /*
   * Initialize flags that are common both to [global] and a local map
   * (that is, they could be inherited from the global section).
   */
  cfm->cfm_flags = gopt.flags & (CFM_BROWSABLE_DIRS |
				 CFM_BROWSABLE_DIRS_FULL |
				 CFM_MOUNT_TYPE_AUTOFS |
				 CFM_SELECTORS_IN_DEFAULTS |
				 CFM_SUN_MAP_SYNTAX );
}