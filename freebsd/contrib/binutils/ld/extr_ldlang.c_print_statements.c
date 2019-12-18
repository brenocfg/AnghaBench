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
struct TYPE_2__ {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  abs_output_section ; 
 int /*<<< orphan*/  print_statement_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ statement_list ; 

__attribute__((used)) static void
print_statements (void)
{
  print_statement_list (statement_list.head, abs_output_section);
}