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
struct option {scalar_t__ val; scalar_t__ has_arg; int /*<<< orphan*/ * flag; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 scalar_t__ OPT_FIRST_LONG_OPT ; 
 struct option* long_opts ; 
 scalar_t__ no_argument ; 
 scalar_t__ optional_argument ; 

__attribute__((used)) static void create_optstring( char *optstring )
{
   char *short_opts = optstring;
   struct option *option;

   // Figure out the short options from our options structure
   for ( option = long_opts; option->name != NULL; option++ )
   {
      if (( option->flag == NULL ) && ( option->val < OPT_FIRST_LONG_OPT ))
      {
         *short_opts++ = (char)option->val;

         if ( option->has_arg != no_argument )
         {
            *short_opts++ = ':';
         }

         // Optional arguments require two ':'
         if ( option->has_arg == optional_argument )
         {
            *short_opts++ = ':';
         }
      }
   }
   *short_opts++ = '\0';
}