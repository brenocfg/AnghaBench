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
struct display {int* value; scalar_t__* entry; } ;
typedef  size_t png_byte ;

/* Variables and functions */
 size_t option_index (struct display*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int
get_option(struct display *dp, const char *opt, int *value)
{
   const png_byte i = option_index(dp, opt, strlen(opt));

   if (dp->entry[i]) /* option was set on command line */
   {
      *value = dp->value[i];
      return 1;
   }

   else
      return 0;
}