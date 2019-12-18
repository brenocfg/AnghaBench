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
typedef  union sltentry {int dummy; } sltentry ;
struct objfile {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SLT (struct objfile*) ; 

__attribute__((used)) static union sltentry *
hpread_get_slt (int index, struct objfile *objfile)
{
  return (union sltentry *) &(SLT (objfile)[index * sizeof (union sltentry)]);
}