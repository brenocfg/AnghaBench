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
typedef  int /*<<< orphan*/  parse_operand_result ;
typedef  int /*<<< orphan*/  group_reloc_type ;

/* Variables and functions */
 int /*<<< orphan*/  parse_address_main (char**,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static parse_operand_result
parse_address_group_reloc (char **str, int i, group_reloc_type type)
{
  return parse_address_main (str, i, 1, type);
}