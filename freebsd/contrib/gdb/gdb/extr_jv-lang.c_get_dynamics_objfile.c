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
struct objfile {int dummy; } ;

/* Variables and functions */
 struct objfile* allocate_objfile (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct objfile* dynamics_objfile ; 

__attribute__((used)) static struct objfile *
get_dynamics_objfile (void)
{
  if (dynamics_objfile == NULL)
    {
      dynamics_objfile = allocate_objfile (NULL, 0);
    }
  return dynamics_objfile;
}