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
typedef  int VCOS_LOG_LEVEL_T ;

/* Variables and functions */
#define  VCOS_LOG_ERROR 133 
#define  VCOS_LOG_INFO 132 
#define  VCOS_LOG_NEVER 131 
#define  VCOS_LOG_TRACE 130 
#define  VCOS_LOG_UNINITIALIZED 129 
#define  VCOS_LOG_WARN 128 

const char *vcos_log_level_to_string( VCOS_LOG_LEVEL_T level )
{
   switch (level)
   {
      case VCOS_LOG_UNINITIALIZED:  return "uninit";
      case VCOS_LOG_NEVER:          return "never";
      case VCOS_LOG_ERROR:          return "error";
      case VCOS_LOG_WARN:           return "warn";
      case VCOS_LOG_INFO:           return "info";
      case VCOS_LOG_TRACE:          return "trace";
   }
   return "???";
}