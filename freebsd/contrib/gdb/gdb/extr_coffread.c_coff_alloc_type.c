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
struct type {int dummy; } ;

/* Variables and functions */
 struct type* alloc_type (int /*<<< orphan*/ ) ; 
 struct type** coff_lookup_type (int) ; 
 int /*<<< orphan*/  current_objfile ; 

__attribute__((used)) static struct type *
coff_alloc_type (int index)
{
  struct type **type_addr = coff_lookup_type (index);
  struct type *type = *type_addr;

  /* If we are referring to a type not known at all yet,
     allocate an empty type for it.
     We will fill it in later if we find out how.  */
  if (type == NULL)
    {
      type = alloc_type (current_objfile);
      *type_addr = type;
    }
  return type;
}