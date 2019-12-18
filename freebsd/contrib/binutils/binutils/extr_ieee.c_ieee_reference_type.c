#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee_handle {TYPE_2__* type_stack; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_3__ {int /*<<< orphan*/  referencep; } ;
struct TYPE_4__ {TYPE_1__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ieee_pointer_type (void*) ; 

__attribute__((used)) static bfd_boolean
ieee_reference_type (void *p)
{
  struct ieee_handle *info = (struct ieee_handle *) p;

  /* IEEE appears to record a normal pointer type, and then use a
     pmisc record to indicate that it is really a reference.  */

  if (! ieee_pointer_type (p))
    return FALSE;
  info->type_stack->type.referencep = TRUE;
  return TRUE;
}