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
 struct type* TYPE_PRIMARY_BASE (struct type*) ; 

int
class_index_in_primary_list (struct type *dclass)
{
  struct type *pbc;		/* primary base class */

  /* Simply recurse on primary base */
  pbc = TYPE_PRIMARY_BASE (dclass);
  if (pbc)
    return 1 + class_index_in_primary_list (pbc);
  else
    return 0;
}