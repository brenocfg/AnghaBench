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
struct itbl_entry {int /*<<< orphan*/  processor; int /*<<< orphan*/  range; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 unsigned long ITBL_ENCODE_PNUM (int /*<<< orphan*/ ) ; 
 unsigned long apply_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long
build_opcode (struct itbl_entry *e)
{
  unsigned long opcode;

  opcode = apply_range (e->value, e->range);
  opcode |= ITBL_ENCODE_PNUM (e->processor);
  return opcode;
}