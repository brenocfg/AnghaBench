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
struct TYPE_4__ {int /*<<< orphan*/  test_gamma_expand16; } ;
typedef  TYPE_1__ png_modifier ;
typedef  int /*<<< orphan*/  png_byte ;

/* Variables and functions */
 int /*<<< orphan*/  gamma_test (TYPE_1__*,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int const,int const,double const,double const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,char*,int const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t safecat (char*,int,size_t,char*) ; 
 size_t safecatd (char*,int,size_t,double const,int) ; 
 size_t safecatn (char*,int,size_t,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void gamma_transform_test(png_modifier *pm,
   const png_byte colour_type, const png_byte bit_depth,
   const int palette_number,
   const int interlace_type, const double file_gamma,
   const double screen_gamma, const png_byte sbit,
   const int use_input_precision, const int scale16)
{
   size_t pos = 0;
   char name[64];

   if (sbit != bit_depth && sbit != 0)
   {
      pos = safecat(name, sizeof name, pos, "sbit(");
      pos = safecatn(name, sizeof name, pos, sbit);
      pos = safecat(name, sizeof name, pos, ") ");
   }

   else
      pos = safecat(name, sizeof name, pos, "gamma ");

   if (scale16)
      pos = safecat(name, sizeof name, pos, "16to8 ");

   pos = safecatd(name, sizeof name, pos, file_gamma, 3);
   pos = safecat(name, sizeof name, pos, "->");
   pos = safecatd(name, sizeof name, pos, screen_gamma, 3);

   gamma_test(pm, colour_type, bit_depth, palette_number, interlace_type,
      file_gamma, screen_gamma, sbit, 0, name, use_input_precision,
      scale16, pm->test_gamma_expand16, 0 , 0, 0);
}