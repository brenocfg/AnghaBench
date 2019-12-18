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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  android_LogPriority ;
struct TYPE_5__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  int VC_CONTAINER_LOG_TYPE_T ;
struct TYPE_4__ {int verbosity; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANDROID_LOG_DEBUG ; 
 int /*<<< orphan*/  ANDROID_LOG_ERROR ; 
 int /*<<< orphan*/  ANDROID_LOG_INFO ; 
 int /*<<< orphan*/  ANDROID_LOG_VERBOSE ; 
 int /*<<< orphan*/  LOG_PRI_VA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_TAG ; 
 int VC_CONTAINER_LOG_DEBUG ; 
 int VC_CONTAINER_LOG_ERROR ; 
 int VC_CONTAINER_LOG_INFO ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  vcos_vlog (char const*,int /*<<< orphan*/ ) ; 
 int verbosity_mask ; 
 int /*<<< orphan*/  vprintf (char const*,int /*<<< orphan*/ ) ; 

void vc_container_log_vargs(VC_CONTAINER_T *ctx, VC_CONTAINER_LOG_TYPE_T type, const char *format, va_list args)
{
   uint32_t verbosity = ctx ? ctx->priv->verbosity : verbosity_mask;

   // If the verbosity is such that the type doesn't need logging quit now.
   if(!(type & verbosity)) return;

#ifdef __ANDROID__
   {
      // Default to Android's "verbose" level (doesn't usually come out)
      android_LogPriority logLevel = ANDROID_LOG_VERBOSE;

      // Where type suggest a higher level is required update logLevel.
      // (Usually type contains only 1 bit as set by the LOG_DEBUG, LOG_ERROR or LOG_INFO macros)
      if (type & VC_CONTAINER_LOG_ERROR)
         logLevel = ANDROID_LOG_ERROR;
      else if (type & VC_CONTAINER_LOG_INFO)
         logLevel = ANDROID_LOG_INFO;
      else if (type & VC_CONTAINER_LOG_DEBUG)
         logLevel = ANDROID_LOG_DEBUG;

      // Actually put the message out.
      LOG_PRI_VA(logLevel, LOG_TAG, format, args);
   }
#else
#ifndef ENABLE_CONTAINERS_STANDALONE
   vcos_vlog(format, args);
#else
   vprintf(format, args); printf("\n");
   fflush(0);
#endif
#endif
}