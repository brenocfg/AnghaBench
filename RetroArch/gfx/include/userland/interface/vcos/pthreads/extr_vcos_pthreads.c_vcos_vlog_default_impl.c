#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
typedef  size_t VCOS_LOG_LEVEL_T ;
struct TYPE_4__ {scalar_t__ want_prefix; } ;
struct TYPE_5__ {char* name; TYPE_1__ flags; } ;
typedef  TYPE_2__ VCOS_LOG_CAT_T ;

/* Variables and functions */
 int /*<<< orphan*/  __android_log_vprint (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * log_fhandle ; 
 int /*<<< orphan*/ * log_prio ; 
 int /*<<< orphan*/  printf_lock ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vcos_use_android_log ; 
 int /*<<< orphan*/  vfprintf (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

void vcos_vlog_default_impl(const VCOS_LOG_CAT_T *cat, VCOS_LOG_LEVEL_T _level, const char *fmt, va_list args)
{
   (void)_level;

#ifdef ANDROID
   if ( vcos_use_android_log )
   {
      __android_log_vprint(log_prio[_level], cat->name, fmt, args);
   }
   else
   {
      vcos_mutex_lock(&printf_lock);
#endif
      if(NULL != log_fhandle)
      {
         if (cat->flags.want_prefix)
            fprintf( log_fhandle, "%s: ", cat->name );
         vfprintf(log_fhandle, fmt, args);
         fputs("\n", log_fhandle);
         fflush(log_fhandle);
      }
#ifdef ANDROID
      vcos_mutex_unlock(&printf_lock);
   }
#endif
}