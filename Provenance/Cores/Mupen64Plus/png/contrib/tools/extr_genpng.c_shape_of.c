#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * shape_fn_ptr ;
struct TYPE_2__ {int /*<<< orphan*/ *** function; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 unsigned int shape_count ; 
 TYPE_1__* shape_defs ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static shape_fn_ptr
shape_of(const char *arg, double width, int f)
{
   unsigned int i;

   for (i=0; i<shape_count; ++i) if (strcmp(shape_defs[i].name, arg) == 0)
   {
      shape_fn_ptr fn = shape_defs[i].function[width != 0][f];

      if (fn != NULL)
         return fn;

      fprintf(stderr, "genpng: %s %s not supported\n",
         width == 0 ? "filled" : "unfilled", arg);
      exit(1);
   }

   fprintf(stderr, "genpng: %s: not a valid shape name\n", arg);
   exit(1);
}