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
struct display {scalar_t__ errset; size_t* entry; int* value; int options; } ;
typedef  size_t png_byte ;
struct TYPE_4__ {int opt; TYPE_1__* values; } ;
struct TYPE_3__ {int value; } ;

/* Variables and functions */
 int LEVEL_MASK ; 
 int LIST ; 
 int OPTION ; 
 int /*<<< orphan*/  USER_ERROR ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  display_log (struct display*,int /*<<< orphan*/ ,char*,int,char const*) ; 
 int find_val (struct display*,size_t,char const*,int) ; 
 size_t option_index (struct display*,char const*,int) ; 
 TYPE_2__* options ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int
opt_check(struct display *dp, const char *arg)
{
   assert(dp->errset == 0);

   if (arg != NULL && arg[0] == '-' && arg[1] == '-')
   {
      int i = 0, negate = (strncmp(arg+2, "no-", 3) == 0), val;
      png_byte j;

      if (negate)
         arg += 5; /* --no- */

      else
         arg += 2; /* -- */

      /* Find the length (expect arg\0 or arg=) */
      while (arg[i] != 0 && arg[i] != '=') ++i;

      /* So arg[0..i-1] is the argument name, this does not return if this isn't
       * a valid option name.
       */
      j = option_index(dp, arg, i);

      /* It matcheth an option; check the remainder. */
      if (arg[i] == 0) /* no specified value, use the default */
      {
         val = options[j].values[negate].value;
         dp->entry[j] = (png_byte)/*SAFE*/(negate + 1U);
      }

      else
      {
         const char *list = arg + (i+1);

         /* Expect a single value here unless this is a list, in which case
          * multiple values are combined.
          */
         if (options[j].opt != LIST)
         {
            /* find_val sets 'dp->entry[j]' to a non-zero value: */
            val = find_val(dp, j, list, strlen(list));

            if (negate)
            {
               if (options[j].opt < OPTION)
                  val = !val;

               else
               {
                  display_log(dp, USER_ERROR,
                        "%.*s: option=arg cannot be negated", i, arg);
                  abort(); /* NOT REACHED */
               }
            }
         }

         else /* multiple options separated by ',' characters */
         {
            /* --no-option negates list values from the default, which should
             * therefore be 'all'.  Notice that if the option list is empty in
             * this case nothing will be removed and therefore --no-option= is
             * the same as --option.
             */
            if (negate)
               val = options[j].values[0].value;

            else
               val = 0;

            while (*list != 0) /* allows option= which sets 0 */
            {
               /* A value is terminated by the end of the list or a ','
                * character.
                */
               int v, iv;

               iv = 0; /* an index into 'list' */
               while (list[++iv] != 0 && list[iv] != ',') {}

               v = find_val(dp, j, list, iv);

               if (negate)
                  val &= ~v;

               else
                  val |= v;

               list += iv;
               if (*list != 0)
                  ++list; /* skip the ',' */
            }
         }
      }

      /* 'val' is the new value, store it for use later and debugging: */
      dp->value[j] = val;

      if (options[j].opt < LEVEL_MASK)
      {
         /* The handling for error levels is to set the level. */
         if (val) /* Set this level */
            dp->options = (dp->options & ~LEVEL_MASK) | options[j].opt;

         else
            display_log(dp, USER_ERROR,
      "%.*s: messages cannot be turned off individually; set a message level",
                  i, arg);
      }

      else if (options[j].opt < OPTION)
      {
         if (val)
            dp->options |= options[j].opt;

         else
            dp->options &= ~options[j].opt;
      }

      return 1; /* this is an option */
   }

   else
      return 0; /* not an option */
}