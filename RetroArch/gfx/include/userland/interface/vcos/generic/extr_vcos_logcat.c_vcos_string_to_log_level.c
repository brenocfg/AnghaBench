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
typedef  int /*<<< orphan*/  VCOS_STATUS_T ;
typedef  int /*<<< orphan*/  VCOS_LOG_LEVEL_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_EINVAL ; 
 int /*<<< orphan*/  VCOS_LOG_ERROR ; 
 int /*<<< orphan*/  VCOS_LOG_INFO ; 
 int /*<<< orphan*/  VCOS_LOG_NEVER ; 
 int /*<<< orphan*/  VCOS_LOG_TRACE ; 
 int /*<<< orphan*/  VCOS_LOG_WARN ; 
 int /*<<< orphan*/  VCOS_SUCCESS ; 
 scalar_t__ strcmp (char const*,char*) ; 

VCOS_STATUS_T vcos_string_to_log_level( const char *str, VCOS_LOG_LEVEL_T *level )
{
   if (strcmp(str,"error") == 0)
      *level = VCOS_LOG_ERROR;
   else if (strcmp(str,"never") == 0)
      *level = VCOS_LOG_NEVER;
   else if (strcmp(str,"warn") == 0)
      *level = VCOS_LOG_WARN;
   else if (strcmp(str,"warning") == 0)
      *level = VCOS_LOG_WARN;
   else if (strcmp(str,"info") == 0)
      *level = VCOS_LOG_INFO;
   else if (strcmp(str,"trace") == 0)
      *level = VCOS_LOG_TRACE;
   else
      return VCOS_EINVAL;

   return VCOS_SUCCESS;
}