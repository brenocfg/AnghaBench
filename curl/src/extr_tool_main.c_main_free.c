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
struct GlobalConfig {int /*<<< orphan*/ * last; int /*<<< orphan*/ * first; } ;

/* Variables and functions */
 int /*<<< orphan*/  PL_ArenaFinish () ; 
 int /*<<< orphan*/  PR_Cleanup () ; 
 scalar_t__ PR_Initialized () ; 
 int /*<<< orphan*/  config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  convert_cleanup () ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  free_globalconfig (struct GlobalConfig*) ; 
 int /*<<< orphan*/  metalink_cleanup () ; 

__attribute__((used)) static void main_free(struct GlobalConfig *config)
{
  /* Cleanup the easy handle */
  /* Main cleanup */
  curl_global_cleanup();
  convert_cleanup();
  metalink_cleanup();
#ifdef USE_NSS
  if(PR_Initialized()) {
    /* prevent valgrind from reporting still reachable mem from NSRP arenas */
    PL_ArenaFinish();
    /* prevent valgrind from reporting possibly lost memory (fd cache, ...) */
    PR_Cleanup();
  }
#endif
  free_globalconfig(config);

  /* Free the config structures */
  config_free(config->last);
  config->first = NULL;
  config->last = NULL;
}