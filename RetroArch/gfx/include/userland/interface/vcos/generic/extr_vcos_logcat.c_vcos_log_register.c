#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  env_name ;
typedef  scalar_t__ VCOS_LOG_LEVEL_T ;
struct TYPE_7__ {int want_prefix; } ;
struct TYPE_8__ {char const* name; scalar_t__ level; int /*<<< orphan*/  refcount; struct TYPE_8__* next; TYPE_1__ flags; } ;
typedef  TYPE_2__ VCOS_LOG_CAT_T ;

/* Variables and functions */
 scalar_t__ VCOS_LOG_ERROR ; 
 scalar_t__ VCOS_LOG_UNINITIALIZED ; 
 char* _VCOS_LOG_LEVEL () ; 
 TYPE_2__ dflt_log_category ; 
 int /*<<< orphan*/  lock ; 
 scalar_t__ read_level (scalar_t__*,char const**,char) ; 
 scalar_t__ read_tok (char*,int,char const**,char) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  vcos_log (char*,char const*) ; 
 int /*<<< orphan*/  vcos_log_info (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_level_to_string (scalar_t__) ; 
 int /*<<< orphan*/  vcos_log_platform_register (TYPE_2__*) ; 
 TYPE_2__* vcos_logging_categories ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 
 int warned_loglevel ; 

void vcos_log_register(const char *name, VCOS_LOG_CAT_T *category)
{
   const char *env;
   VCOS_LOG_CAT_T *i;

   category->name  = name;
   if ( category->level == VCOS_LOG_UNINITIALIZED )
   {
      category->level = VCOS_LOG_ERROR;
   }
   category->flags.want_prefix = (category != &dflt_log_category );

   vcos_mutex_lock(&lock);

   /* is it already registered? */
   for (i = vcos_logging_categories; i ; i = i->next )
   {
      if (i == category)
      {
         i->refcount++;
         break;
      }
   }

   if (!i)
   {
      /* not yet registered */
      category->next = vcos_logging_categories;
      vcos_logging_categories = category;
      category->refcount++;

      vcos_log_platform_register(category);
   }

   vcos_mutex_unlock(&lock);

   /* Check to see if this log level has been enabled. Look for
    * (<category:level>,)*
    *
    * VC_LOGLEVEL=ilcs:info,vchiq:warn
    */

   env = _VCOS_LOG_LEVEL();
   if (env && env[0])
   {
      do
      {
         char env_name[64];
         VCOS_LOG_LEVEL_T level;
         if (read_tok(env_name, sizeof(env_name), &env, ':') &&
             read_level(&level, &env, ','))
         {
            if (strcmp(env_name, name) == 0 || strcmp(env_name, "*") == 0)
            {
               // we could match both * and env_name, so make sure * comes
               // first in the logging_level string
               category->level = level;
            }
         }
         else
         {
            if (!warned_loglevel)
            {
                vcos_log("VC_LOGLEVEL format invalid at %s\n", env);
                warned_loglevel = 1;
            }
            return;
         }
      } while (env[0] != '\0');
   }

   vcos_log_info( "Registered log category '%s' with level %s",
                  category->name,
                  vcos_log_level_to_string( category->level ));
}