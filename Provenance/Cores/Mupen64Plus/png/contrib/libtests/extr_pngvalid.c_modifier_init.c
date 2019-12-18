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
struct TYPE_4__ {unsigned int sbitlow; int limit; int test_tRNS; int test_lbg; int test_lbg_gamma_threshold; int test_lbg_gamma_transform; int test_lbg_gamma_sbit; int test_lbg_gamma_composition; scalar_t__ log; scalar_t__ test_exhaustive; scalar_t__ test_gamma_expand16; scalar_t__ test_gamma_alpha_mode; scalar_t__ test_gamma_background; scalar_t__ test_gamma_scale16; scalar_t__ test_gamma_sbit; scalar_t__ test_gamma_transform; scalar_t__ test_gamma_threshold; scalar_t__ assume_16_bit_calculations; scalar_t__ calculations_use_input_precision; scalar_t__ use_input_precision_16to8; scalar_t__ use_input_precision_sbit; scalar_t__ use_input_precision; scalar_t__ test_transform; scalar_t__ test_size; scalar_t__ test_standard; int /*<<< orphan*/  interlace_type; scalar_t__ use_update_info; scalar_t__ error_indexed; scalar_t__ error_color_16; scalar_t__ error_color_8; scalar_t__ error_gray_16; scalar_t__ error_gray_8; scalar_t__ error_gray_4; scalar_t__ error_gray_2; scalar_t__ log16; scalar_t__ log8; scalar_t__ maxcalcG; scalar_t__ maxcalc16; scalar_t__ maxabs16; scalar_t__ maxpc16; scalar_t__ maxout16; scalar_t__ maxcalc8; scalar_t__ maxabs8; scalar_t__ maxpc8; scalar_t__ maxout8; scalar_t__ test_uses_encoding; scalar_t__ repeat; scalar_t__ encoding_ignored; scalar_t__ encoding_counter; scalar_t__ current_encoding; scalar_t__ nencodings; scalar_t__ encodings; scalar_t__ current_gamma; scalar_t__ gammas; scalar_t__ ngamma_tests; scalar_t__ ngammas; int /*<<< orphan*/  state; int /*<<< orphan*/ * modifications; int /*<<< orphan*/  this; } ;
typedef  TYPE_1__ png_modifier ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_INTERLACE_NONE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  modifier_start ; 
 int /*<<< orphan*/  store_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
modifier_init(png_modifier *pm)
{
   memset(pm, 0, sizeof *pm);
   store_init(&pm->this);
   pm->modifications = NULL;
   pm->state = modifier_start;
   pm->sbitlow = 1U;
   pm->ngammas = 0;
   pm->ngamma_tests = 0;
   pm->gammas = 0;
   pm->current_gamma = 0;
   pm->encodings = 0;
   pm->nencodings = 0;
   pm->current_encoding = 0;
   pm->encoding_counter = 0;
   pm->encoding_ignored = 0;
   pm->repeat = 0;
   pm->test_uses_encoding = 0;
   pm->maxout8 = pm->maxpc8 = pm->maxabs8 = pm->maxcalc8 = 0;
   pm->maxout16 = pm->maxpc16 = pm->maxabs16 = pm->maxcalc16 = 0;
   pm->maxcalcG = 0;
   pm->limit = 4E-3;
   pm->log8 = pm->log16 = 0; /* Means 'off' */
   pm->error_gray_2 = pm->error_gray_4 = pm->error_gray_8 = 0;
   pm->error_gray_16 = pm->error_color_8 = pm->error_color_16 = 0;
   pm->error_indexed = 0;
   pm->use_update_info = 0;
   pm->interlace_type = PNG_INTERLACE_NONE;
   pm->test_standard = 0;
   pm->test_size = 0;
   pm->test_transform = 0;
#  ifdef PNG_WRITE_tRNS_SUPPORTED
      pm->test_tRNS = 1;
#  else
      pm->test_tRNS = 0;
#  endif
   pm->use_input_precision = 0;
   pm->use_input_precision_sbit = 0;
   pm->use_input_precision_16to8 = 0;
   pm->calculations_use_input_precision = 0;
   pm->assume_16_bit_calculations = 0;
   pm->test_gamma_threshold = 0;
   pm->test_gamma_transform = 0;
   pm->test_gamma_sbit = 0;
   pm->test_gamma_scale16 = 0;
   pm->test_gamma_background = 0;
   pm->test_gamma_alpha_mode = 0;
   pm->test_gamma_expand16 = 0;
   pm->test_lbg = 1;
   pm->test_lbg_gamma_threshold = 1;
   pm->test_lbg_gamma_transform = 1;
   pm->test_lbg_gamma_sbit = 1;
   pm->test_lbg_gamma_composition = 1;
   pm->test_exhaustive = 0;
   pm->log = 0;

   /* Rely on the memset for all the other fields - there are no pointers */
}