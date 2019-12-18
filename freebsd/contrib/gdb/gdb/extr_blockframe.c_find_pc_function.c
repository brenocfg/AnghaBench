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
struct symbol {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  find_pc_mapped_section (int /*<<< orphan*/ ) ; 
 struct symbol* find_pc_sect_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct symbol *
find_pc_function (CORE_ADDR pc)
{
  return find_pc_sect_function (pc, find_pc_mapped_section (pc));
}