#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cfm_flags; } ;
typedef  TYPE_1__ cf_map_t ;

/* Variables and functions */
 int /*<<< orphan*/  CFM_SUN_MAP_SYNTAX ; 
 scalar_t__ STREQ (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
ropt_sun_map_syntax(const char *val, cf_map_t *cfm)
{
  if (STREQ(val, "yes")) {
    cfm->cfm_flags |= CFM_SUN_MAP_SYNTAX;
    return 0;

  } else if (STREQ(val, "no")) {
    cfm->cfm_flags &= ~CFM_SUN_MAP_SYNTAX;
    return 0;
  }

  fprintf(stderr, "conf: unknown value to sun_map_syntax \"%s\"\n", val);
  return 1;			/* unknown value */
}