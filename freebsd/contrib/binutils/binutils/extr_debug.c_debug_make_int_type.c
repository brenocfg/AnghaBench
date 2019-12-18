#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  kint; } ;
struct debug_type {TYPE_1__ u; } ;
struct debug_handle {int dummy; } ;
typedef  struct debug_type* debug_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_KIND_INT ; 
 struct debug_type* DEBUG_TYPE_NULL ; 
 struct debug_type* debug_make_type (struct debug_handle*,int /*<<< orphan*/ ,unsigned int) ; 

debug_type
debug_make_int_type (void *handle, unsigned int size, bfd_boolean unsignedp)
{
  struct debug_handle *info = (struct debug_handle *) handle;
  struct debug_type *t;

  t = debug_make_type (info, DEBUG_KIND_INT, size);
  if (t == NULL)
    return DEBUG_TYPE_NULL;

  t->u.kint = unsignedp;

  return t;
}