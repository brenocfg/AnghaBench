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
struct objc_method {void* imp; void* types; void* name; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 void* read_memory_unsigned_integer (scalar_t__,int) ; 

__attribute__((used)) static void 
read_objc_method (CORE_ADDR addr, struct objc_method *method)
{
  method->name  = read_memory_unsigned_integer (addr + 0, 4);
  method->types = read_memory_unsigned_integer (addr + 4, 4);
  method->imp   = read_memory_unsigned_integer (addr + 8, 4);
}