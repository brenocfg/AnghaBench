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
struct dwarf1_unit {struct dwarf1_func* func_list; } ;
struct dwarf1_func {struct dwarf1_func* prev; } ;
struct dwarf1_debug {int /*<<< orphan*/  abfd; } ;
typedef  int bfd_size_type ;

/* Variables and functions */
 struct dwarf1_func* bfd_zalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct dwarf1_func *
alloc_dwarf1_func (struct dwarf1_debug* stash, struct dwarf1_unit* aUnit)
{
  bfd_size_type amt = sizeof (struct dwarf1_func);

  struct dwarf1_func* x = bfd_zalloc (stash->abfd, amt);
  x->prev = aUnit->func_list;
  aUnit->func_list = x;

  return x;
}