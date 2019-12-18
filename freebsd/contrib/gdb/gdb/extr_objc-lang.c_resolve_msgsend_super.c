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
struct objc_super {scalar_t__ class; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ OBJC_FETCH_POINTER_ARGUMENT (int) ; 
 scalar_t__ find_implementation_from_class (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  read_objc_super (scalar_t__,struct objc_super*) ; 

__attribute__((used)) static int
resolve_msgsend_super (CORE_ADDR pc, CORE_ADDR *new_pc)
{
  struct objc_super sstr;

  CORE_ADDR super;
  CORE_ADDR sel;
  CORE_ADDR res;

  super = OBJC_FETCH_POINTER_ARGUMENT (0);
  sel = OBJC_FETCH_POINTER_ARGUMENT (1);

  read_objc_super (super, &sstr);
  if (sstr.class == 0)
    return 0;
  
  res = find_implementation_from_class (sstr.class, sel);
  if (new_pc != 0)
    *new_pc = res;
  if (res == 0)
    return 1;
  return 0;
}