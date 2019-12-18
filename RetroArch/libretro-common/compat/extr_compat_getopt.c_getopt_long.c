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
struct option {int dummy; } ;

/* Variables and functions */
 int find_long_index (char**) ; 
 int find_short_index (char**) ; 
 size_t optind ; 
 int parse_long (struct option const*,char**) ; 
 int parse_short (char const*,char**) ; 
 int /*<<< orphan*/  retro_assert (int) ; 
 int /*<<< orphan*/  shuffle_block (char**,char**,char**) ; 

int getopt_long(int argc, char *argv[],
      const char *optstring, const struct option *longopts, int *longindex)
{
   int short_index, long_index;

   (void)longindex;

   if (optind == 0)
      optind = 1;

   if (argc < 2)
      return -1;

   short_index = find_short_index(&argv[optind]);
   long_index  = find_long_index(&argv[optind]);

   /* We're done here. */
   if (short_index == -1 && long_index == -1)
      return -1;

   /* Reorder argv so that non-options come last.
    * Non-POSIXy, but that's what getopt does by default. */
   if ((short_index > 0) && ((short_index < long_index) || (long_index == -1)))
   {
      shuffle_block(&argv[optind], &argv[optind + short_index], &argv[argc]);
      short_index = 0;
   }
   else if ((long_index > 0) && ((long_index < short_index)
            || (short_index == -1)))
   {
      shuffle_block(&argv[optind], &argv[optind + long_index], &argv[argc]);
      long_index = 0;
   }

   retro_assert(short_index == 0 || long_index == 0);

   if (short_index == 0)
      return parse_short(optstring, &argv[optind]);
   if (long_index == 0)
      return parse_long(longopts, &argv[optind]);

   return '?';
}