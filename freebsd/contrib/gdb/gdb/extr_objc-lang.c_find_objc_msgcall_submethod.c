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
struct objc_submethod_helper_data {int (* f ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * new_pc; int /*<<< orphan*/  pc; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_MASK_ALL ; 
 scalar_t__ catch_errors (int /*<<< orphan*/ ,void*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_objc_msgcall_submethod_helper ; 

__attribute__((used)) static int 
find_objc_msgcall_submethod (int (*f) (CORE_ADDR, CORE_ADDR *),
			     CORE_ADDR pc, 
			     CORE_ADDR *new_pc)
{
  struct objc_submethod_helper_data s;

  s.f = f;
  s.pc = pc;
  s.new_pc = new_pc;

  if (catch_errors (find_objc_msgcall_submethod_helper,
		    (void *) &s,
		    "Unable to determine target of Objective-C method call (ignoring):\n",
		    RETURN_MASK_ALL) == 0) 
    return 1;
  else 
    return 0;
}