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
struct dwarf2_fde {int /*<<< orphan*/  next; } ;
struct comp_unit {int /*<<< orphan*/  objfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwarf2_frame_objfile_data ; 
 int /*<<< orphan*/  objfile_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_objfile_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dwarf2_fde*) ; 

__attribute__((used)) static void
add_fde (struct comp_unit *unit, struct dwarf2_fde *fde)
{
  fde->next = objfile_data (unit->objfile, dwarf2_frame_objfile_data);
  set_objfile_data (unit->objfile, dwarf2_frame_objfile_data, fde);
}