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
struct display {size_t* entry; scalar_t__ errset; } ;
typedef  size_t png_byte ;
struct TYPE_4__ {size_t value_count; int /*<<< orphan*/  name; TYPE_1__* values; } ;
struct TYPE_3__ {scalar_t__* name; int value; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERNAL_ERROR ; 
 int INT_MAX ; 
 int INT_MIN ; 
 int /*<<< orphan*/  USER_ERROR ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  display_log (struct display*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,char const*) ; 
 TYPE_2__* options ; 
 scalar_t__* range_hi ; 
 scalar_t__* range_lo ; 
 scalar_t__ strncmp (scalar_t__*,char const*,size_t) ; 
 long strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
find_val(struct display *dp, png_byte opt, const char *str, size_t len)
   /* Like option_index but sets (index+i) of the entry in options[opt] that
    * matches str[0..len-1] into dp->entry[opt] as well as returning the actual
    * value.
    */
{
   int rlo = INT_MAX, rhi = INT_MIN;
   png_byte j, irange = 0;

   for (j=1U; j<=options[opt].value_count; ++j)
   {
      if (strncmp(options[opt].values[j-1U].name, str, len) == 0 &&
          options[opt].values[j-1U].name[len] == 0)
      {
         dp->entry[opt] = j;
         return options[opt].values[j-1U].value;
      }
      else if (options[opt].values[j-1U].name == range_lo)
         rlo = options[opt].values[j-1U].value, irange = j;
      else if (options[opt].values[j-1U].name == range_hi)
         rhi = options[opt].values[j-1U].value;
   }

   /* No match on the name, but there may be a range. */
   if (irange > 0)
   {
      char *ep = NULL;
      long l = strtol(str, &ep, 0);

      if (ep == str+len && l >= rlo && l <= rhi)
      {
         dp->entry[opt] = irange; /* range_lo */
         return (int)/*SAFE*/l;
      }
   }

   display_log(dp, dp->errset ? INTERNAL_ERROR : USER_ERROR,
         "%s: unknown value setting '%.*s'", options[opt].name,
         (int)/*SAFE*/len, str);
   abort(); /* NOT REACHED */
}