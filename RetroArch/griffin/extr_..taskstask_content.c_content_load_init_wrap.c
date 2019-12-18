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
struct rarch_main_wrap {char* content_path; char* sram_path; char* state_path; char* config_path; char* libretro_path; scalar_t__ verbose; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_NO_CONTENT_STARTING_DUMMY_CORE ; 
 int /*<<< orphan*/  RARCH_LOG (char*,...) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 char* strdup (char*) ; 

__attribute__((used)) static void content_load_init_wrap(
      const struct rarch_main_wrap *args,
      int *argc, char **argv)
{
   int i;

   *argc = 0;
   argv[(*argc)++] = strdup("retroarch");

   if (args->content_path)
   {
      RARCH_LOG("Using content: %s.\n", args->content_path);
      argv[(*argc)++] = strdup(args->content_path);
   }
#ifdef HAVE_MENU
   else
   {
      RARCH_LOG("%s\n",
            msg_hash_to_str(MSG_NO_CONTENT_STARTING_DUMMY_CORE));
      argv[(*argc)++] = strdup("--menu");
   }
#endif

   if (args->sram_path)
   {
      argv[(*argc)++] = strdup("-s");
      argv[(*argc)++] = strdup(args->sram_path);
   }

   if (args->state_path)
   {
      argv[(*argc)++] = strdup("-S");
      argv[(*argc)++] = strdup(args->state_path);
   }

   if (args->config_path)
   {
      argv[(*argc)++] = strdup("-c");
      argv[(*argc)++] = strdup(args->config_path);
   }

#ifdef HAVE_DYNAMIC
   if (args->libretro_path)
   {
      argv[(*argc)++] = strdup("-L");
      argv[(*argc)++] = strdup(args->libretro_path);
   }
#endif

   if (args->verbose)
      argv[(*argc)++] = strdup("-v");

   for (i = 0; i < *argc; i++)
      RARCH_LOG("arg #%d: %s\n", i, argv[i]);
}