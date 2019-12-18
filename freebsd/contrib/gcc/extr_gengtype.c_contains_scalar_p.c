#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* type_p ;
struct TYPE_5__ {TYPE_3__* p; } ;
struct TYPE_6__ {TYPE_1__ a; } ;
struct TYPE_7__ {int kind; TYPE_2__ u; } ;

/* Variables and functions */
#define  TYPE_ARRAY 130 
#define  TYPE_POINTER 129 
#define  TYPE_STRING 128 

__attribute__((used)) static int
contains_scalar_p (type_p t)
{
  switch (t->kind)
    {
    case TYPE_STRING:
    case TYPE_POINTER:
      return 0;
    case TYPE_ARRAY:
      return contains_scalar_p (t->u.a.p);
    default:
      /* Could also check for structures that have no non-pointer
	 fields, but there aren't enough of those to worry about.  */
      return 1;
    }
}