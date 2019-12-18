#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct display {int* entry; int* value; } ;
typedef  size_t png_byte ;
struct TYPE_4__ {TYPE_1__* values; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  advance_opt (struct display*,size_t const,int /*<<< orphan*/ ) ; 
 char const* all ; 
 TYPE_2__* options ; 
 int /*<<< orphan*/  record_opt (struct display*,size_t const,char const*) ; 

__attribute__((used)) static int
getallopts_(struct display *dp, const png_byte opt, int *value, int record)
   /* Like getop but iterate over all the values if the option was set to "all".
    */
{
   if (dp->entry[opt]) /* option was set on command line */
   {
      /* Simple, single value, entries don't have a stack frame and have a fixed
       * value (it doesn't change once set on the command line).  Otherwise the
       * value (entry) selected from the command line is 'all':
       */
      const char *entry_name = options[opt].values[dp->entry[opt]-1].name;

      if (entry_name == all)
         (void)advance_opt(dp, opt, 0/*do not search; iterate*/);

      else if (record)
         record_opt(dp, opt, entry_name);

      *value = dp->value[opt];
      return 1; /* set */
   }

   else
      return 0; /* not set */
}