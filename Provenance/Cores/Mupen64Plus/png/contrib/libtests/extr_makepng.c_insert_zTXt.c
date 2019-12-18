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
struct TYPE_4__ {scalar_t__ compression; } ;
typedef  TYPE_1__ png_text ;
typedef  int /*<<< orphan*/  png_structp ;
typedef  int /*<<< orphan*/  png_infop ;
typedef  int /*<<< orphan*/ * png_charpp ;

/* Variables and functions */
 int /*<<< orphan*/  check_param_count (int,int) ; 
 int /*<<< orphan*/  clear_text (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_text (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
insert_zTXt(png_structp png_ptr, png_infop info_ptr, int nparams,
   png_charpp params)
{
   png_text text;

   check_param_count(nparams, 2);
   clear_text(&text, params[0]);
   text.compression = 0; /* deflate */
   set_text(png_ptr, info_ptr, &text, params[1]);
}