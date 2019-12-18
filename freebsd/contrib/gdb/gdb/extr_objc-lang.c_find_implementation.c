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
struct objc_object {scalar_t__ isa; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ find_implementation_from_class (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  read_objc_object (scalar_t__,struct objc_object*) ; 

__attribute__((used)) static CORE_ADDR
find_implementation (CORE_ADDR object, CORE_ADDR sel)
{
  struct objc_object ostr;

  if (object == 0)
    return 0;
  read_objc_object (object, &ostr);
  if (ostr.isa == 0)
    return 0;

  return find_implementation_from_class (ostr.isa, sel);
}