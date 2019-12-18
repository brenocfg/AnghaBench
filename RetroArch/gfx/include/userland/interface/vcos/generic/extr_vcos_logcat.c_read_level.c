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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  VCOS_LOG_LEVEL_T ;

/* Variables and functions */
 scalar_t__ VCOS_SUCCESS ; 
 scalar_t__ read_tok (char*,int,char const**,char) ; 
 int /*<<< orphan*/  vcos_log (char*,char*) ; 
 scalar_t__ vcos_string_to_log_level (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_level(VCOS_LOG_LEVEL_T *level, const char **pstr, char sep)
{
   char buf[16];
   int ret = 1;
   if (read_tok(buf,sizeof(buf),pstr,sep))
   {
      if (vcos_string_to_log_level(buf,level) != VCOS_SUCCESS)
      {
         vcos_log("Invalid trace level '%s'\n", buf);
         ret = 0;
      }
   }
   else
   {
      ret = 0;
   }
   return ret;
}