#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ cfm_dir; } ;
typedef  TYPE_1__ cf_map_t ;

/* Variables and functions */
 scalar_t__ STREQ (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int ropt_browsable_dirs (char const*,TYPE_1__*) ; 
 int ropt_map_defaults (char const*,TYPE_1__*) ; 
 int ropt_map_name (char const*,TYPE_1__*) ; 
 int ropt_map_options (char const*,TYPE_1__*) ; 
 int ropt_map_type (char const*,TYPE_1__*) ; 
 int ropt_mount_type (char const*,TYPE_1__*) ; 
 int ropt_search_path (char const*,TYPE_1__*) ; 
 int ropt_sun_map_syntax (char const*,TYPE_1__*) ; 
 int ropt_tag (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ xstrdup (char const*) ; 

__attribute__((used)) static int
process_regular_option(const char *section, const char *key, const char *val, cf_map_t *cfm)
{
  /* ensure that val is valid */
  if (!section || section[0] == '\0' ||
      !key || key[0] == '\0' ||
      !val || val[0] == '\0' ||
      !cfm) {
    fprintf(stderr, "conf: process_regular_option: null entries\n");
    return 1;
  }

  /* check if initializing a new map */
  if (!cfm->cfm_dir)
    cfm->cfm_dir = xstrdup(section);

  /* check for each possible field */
  if (STREQ(key, "browsable_dirs"))
    return ropt_browsable_dirs(val, cfm);

  if (STREQ(key, "map_name"))
    return ropt_map_name(val, cfm);

  if (STREQ(key, "map_defaults"))
    return ropt_map_defaults(val, cfm);

  if (STREQ(key, "map_options"))
    return ropt_map_options(val, cfm);

  if (STREQ(key, "map_type"))
    return ropt_map_type(val, cfm);

  if (STREQ(key, "mount_type"))
    return ropt_mount_type(val, cfm);

  if (STREQ(key, "search_path"))
    return ropt_search_path(val, cfm);

  if (STREQ(key, "sun_map_syntax"))
    return ropt_sun_map_syntax(val, cfm);

  if (STREQ(key, "tag"))
    return ropt_tag(val, cfm);

  fprintf(stderr, "conf: unknown regular key \"%s\" for section \"%s\"\n",
	  key, section);
  return 1;			/* failed to match any command */
}