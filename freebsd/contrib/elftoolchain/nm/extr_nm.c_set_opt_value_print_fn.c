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
typedef  enum radix { ____Placeholder_radix } radix ;
struct TYPE_2__ {int /*<<< orphan*/ * value_print_fn; int /*<<< orphan*/ * size_print_fn; } ;

/* Variables and functions */
#define  RADIX_DEC 130 
#define  RADIX_HEX 129 
#define  RADIX_OCT 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__ nm_opts ; 
 int /*<<< orphan*/  sym_size_dec_print ; 
 int /*<<< orphan*/  sym_size_hex_print ; 
 int /*<<< orphan*/  sym_size_oct_print ; 
 int /*<<< orphan*/  sym_value_dec_print ; 
 int /*<<< orphan*/  sym_value_hex_print ; 
 int /*<<< orphan*/  sym_value_oct_print ; 

__attribute__((used)) static void
set_opt_value_print_fn(enum radix t)
{

	switch (t) {
	case RADIX_OCT:
		nm_opts.value_print_fn = &sym_value_oct_print;
		nm_opts.size_print_fn = &sym_size_oct_print;

		break;
	case RADIX_DEC:
		nm_opts.value_print_fn = &sym_value_dec_print;
		nm_opts.size_print_fn = &sym_size_dec_print;

		break;
	case RADIX_HEX:
	default :
		nm_opts.value_print_fn = &sym_value_hex_print;
		nm_opts.size_print_fn  = &sym_size_hex_print;
	}

	assert(nm_opts.value_print_fn != NULL &&
	    "nm_opts.value_print_fn is null");
}