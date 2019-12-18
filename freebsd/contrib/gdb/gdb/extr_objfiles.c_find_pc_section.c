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
struct obj_section {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  find_pc_mapped_section (int /*<<< orphan*/ ) ; 
 struct obj_section* find_pc_sect_section (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct obj_section *
find_pc_section (CORE_ADDR pc)
{
  return find_pc_sect_section (pc, find_pc_mapped_section (pc));
}