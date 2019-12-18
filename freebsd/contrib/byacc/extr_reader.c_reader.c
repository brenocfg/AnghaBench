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

/* Variables and functions */
 int /*<<< orphan*/  banner ; 
 int /*<<< orphan*/  check_symbols () ; 
 int /*<<< orphan*/  code_file ; 
 int /*<<< orphan*/  create_symbol_table () ; 
 scalar_t__ destructor ; 
 int /*<<< orphan*/  finalize_destructors () ; 
 int /*<<< orphan*/  free_symbol_table () ; 
 int /*<<< orphan*/  free_symbols () ; 
 int /*<<< orphan*/  free_tags () ; 
 int /*<<< orphan*/  pack_grammar () ; 
 int /*<<< orphan*/  pack_names () ; 
 int /*<<< orphan*/  pack_symbols () ; 
 int /*<<< orphan*/  print_grammar () ; 
 int /*<<< orphan*/  read_declarations () ; 
 int /*<<< orphan*/  read_grammar () ; 
 int /*<<< orphan*/  write_section (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
reader(void)
{
    write_section(code_file, banner);
    create_symbol_table();
    read_declarations();
    read_grammar();
    free_symbol_table();
    pack_names();
    check_symbols();
    pack_symbols();
    pack_grammar();
    free_symbols();
    print_grammar();
#if defined(YYBTYACC)
    if (destructor)
	finalize_destructors();
#endif
    free_tags();
}