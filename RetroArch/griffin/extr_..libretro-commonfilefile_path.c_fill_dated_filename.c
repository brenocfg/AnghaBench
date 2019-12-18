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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;

/* Variables and functions */
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strftime (char*,size_t,char*,struct tm const*) ; 
 size_t strlcat (char*,char const*,size_t) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

size_t fill_dated_filename(char *out_filename,
      const char *ext, size_t size)
{
   time_t       cur_time = time(NULL);
   const struct tm* tm_  = localtime(&cur_time);

   strftime(out_filename, size,
         "RetroArch-%m%d-%H%M%S", tm_);
   return strlcat(out_filename, ext, size);
}