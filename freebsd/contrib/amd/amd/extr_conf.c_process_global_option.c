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
struct _func_map {int (* func ) (char const*) ;scalar_t__ name; } ;

/* Variables and functions */
 scalar_t__ FSTREQ (scalar_t__,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 struct _func_map* glob_functable ; 
 int /*<<< orphan*/  stderr ; 
 int stub1 (char const*) ; 

__attribute__((used)) static int
process_global_option(const char *key, const char *val)
{
  struct _func_map *gfp;

  /* ensure that val is valid */
  if (!val || val[0] == '\0')
    return 1;

  /*
   * search for global function.
   */
  for (gfp = glob_functable; gfp->name; gfp++)
    if (FSTREQ(gfp->name, key))
      return (gfp->func)(val);

  fprintf(stderr, "conf: unknown global key: \"%s\"\n", key);
  return 1;			/* failed to match any command */
}