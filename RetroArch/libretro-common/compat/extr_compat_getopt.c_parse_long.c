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
struct option {int* flag; int val; scalar_t__ has_arg; scalar_t__ name; } ;

/* Variables and functions */
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 

__attribute__((used)) static int parse_long(const struct option *longopts, char * const *argv)
{
   size_t indice;
   const struct option *opt = NULL;
   for (indice = 0; longopts[indice].name; indice++)
   {
      if (!strcmp(longopts[indice].name, &argv[0][2]))
      {
         opt = &longopts[indice];
         break;
      }
   }

   if (!opt)
      return '?';

   /* getopt_long has an "optional" arg, but we don't bother with that. */
   if (opt->has_arg && !argv[1])
      return '?';

   if (opt->has_arg)
   {
      optarg = argv[1];
      optind += 2;
   }
   else
      optind++;

   if (opt->flag)
   {
      *opt->flag = opt->val;
      return 0;
   }

   return opt->val;
}