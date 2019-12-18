#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  address; int /*<<< orphan*/  section_name; } ;
typedef  TYPE_1__ lang_address_statement_type ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  exp_print_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_nl () ; 

__attribute__((used)) static void
print_address_statement (lang_address_statement_type *address)
{
  minfo (_("Address of section %s set to "), address->section_name);
  exp_print_tree (address->address);
  print_nl ();
}