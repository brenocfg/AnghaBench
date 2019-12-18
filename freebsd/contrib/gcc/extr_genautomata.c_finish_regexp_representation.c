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

/* Variables and functions */
 int /*<<< orphan*/  irp ; 
 int /*<<< orphan*/  obstack_blank_fast (int /*<<< orphan*/ *,int) ; 
 int obstack_object_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
finish_regexp_representation (void)
{
  int length = obstack_object_size (&irp);

  obstack_blank_fast (&irp, -length);
}