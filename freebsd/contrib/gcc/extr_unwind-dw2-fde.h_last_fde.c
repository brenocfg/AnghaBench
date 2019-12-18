#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct object {char* fde_end; } ;
struct TYPE_3__ {scalar_t__ length; } ;
typedef  TYPE_1__ fde ;

/* Variables and functions */

__attribute__((used)) static inline int
last_fde (struct object *obj __attribute__ ((__unused__)), const fde *f)
{
#ifdef DWARF2_OBJECT_END_PTR_EXTENSION
  return (char *)f == obj->fde_end || f->length == 0;
#else
  return f->length == 0;
#endif
}