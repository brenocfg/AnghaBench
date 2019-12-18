#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  this; } ;
typedef  TYPE_1__ png_modifier ;
typedef  int /*<<< orphan*/  png_byte ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEPTH (int) ; 
 int FILE_NAME_SIZE ; 
 int INTERLACE_LAST ; 
 int PNG_INTERLACE_NONE ; 
 int /*<<< orphan*/  do_own_interlace ; 
 int /*<<< orphan*/  error_test ; 
 scalar_t__ fail (TYPE_1__* const) ; 
 int /*<<< orphan*/  make_error (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int,unsigned int,char*) ; 
 int /*<<< orphan*/  standard_name (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
make_errors(png_modifier* const pm, png_byte const colour_type,
    int bdlo, int const bdhi)
{
   for (; bdlo <= bdhi; ++bdlo)
   {
      int interlace_type;

      for (interlace_type = PNG_INTERLACE_NONE;
           interlace_type < INTERLACE_LAST; ++interlace_type)
      {
         unsigned int test;
         char name[FILE_NAME_SIZE];

         standard_name(name, sizeof name, 0, colour_type, 1<<bdlo, 0,
            interlace_type, 0, 0, do_own_interlace);

         for (test=0; test<ARRAY_SIZE(error_test); ++test)
         {
            make_error(&pm->this, colour_type, DEPTH(bdlo), interlace_type,
               test, name);

            if (fail(pm))
               return 0;
         }
      }
   }

   return 1; /* keep going */
}