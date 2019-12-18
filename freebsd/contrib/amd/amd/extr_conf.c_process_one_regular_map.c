#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* cfm_dir; int cfm_flags; char* cfm_opts; int /*<<< orphan*/  cfm_name; int /*<<< orphan*/  cfm_tag; } ;
typedef  TYPE_1__ cf_map_t ;

/* Variables and functions */
 scalar_t__ STREQ (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ conf_tag ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  root_newmap (char*,char*,int /*<<< orphan*/ ,TYPE_1__ const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
process_one_regular_map(const cf_map_t *cfm)
{
  if (!cfm->cfm_name) {
    fprintf(stderr, "conf: map_name must be defined for map \"%s\"\n", cfm->cfm_dir);
    return 1;
  }
  /*
   * If map has no tag defined, process the map.
   * If no conf_tag was set in amd -T, process all untagged entries.
   * If a tag is defined, then process it only if it matches the map tag.
   */
  if (!cfm->cfm_tag ||
      (conf_tag && STREQ(cfm->cfm_tag, conf_tag))) {
#ifdef DEBUG_CONF
    fprintf(stderr, "processing map %s (flags=0x%x)...\n",
	    cfm->cfm_dir, cfm->cfm_flags);
#endif /* DEBUG_CONF */
    root_newmap(cfm->cfm_dir,
		cfm->cfm_opts ? cfm->cfm_opts : "",
		cfm->cfm_name,
		cfm);
  } else {
    fprintf(stderr, "skipping map %s...\n", cfm->cfm_dir);
  }

  return 0;
}