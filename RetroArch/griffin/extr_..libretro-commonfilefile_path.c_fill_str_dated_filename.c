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
typedef  int /*<<< orphan*/  format ;

/* Variables and functions */
 int /*<<< orphan*/  fill_pathname_join_concat_noext (char*,char const*,char*,char const*,size_t) ; 
 int /*<<< orphan*/  fill_pathname_noext (char*,char const*,char*,size_t) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm const*) ; 
 scalar_t__ string_is_empty (char const*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void fill_str_dated_filename(char *out_filename,
      const char *in_str, const char *ext, size_t size)
{
   char format[256];
   time_t cur_time      = time(NULL);
   const struct tm* tm_ = localtime(&cur_time);

   format[0]            = '\0';

   if (string_is_empty(ext))
   {
      strftime(format, sizeof(format), "-%y%m%d-%H%M%S", tm_);
      fill_pathname_noext(out_filename, in_str, format, size);
   }
   else
   {
      strftime(format, sizeof(format), "-%y%m%d-%H%M%S.", tm_);

      fill_pathname_join_concat_noext(out_filename,
            in_str, format, ext,
            size);
   }
}