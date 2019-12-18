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
struct TYPE_3__ {int type; scalar_t__ i; scalar_t__* s; } ;
typedef  TYPE_1__ obj_attribute ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static bfd_boolean
is_default_attr (obj_attribute *attr)
{
  if ((attr->type & 1) && attr->i != 0)
    return FALSE;
  if ((attr->type & 2) && attr->s && *attr->s)
    return FALSE;

  return TRUE;
}