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
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 void* obstack_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obstack_blank (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  obstack_finish (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
create_node (size_t size)
{
  void *result;

  obstack_blank (&irp, size);
  result = obstack_base (&irp);
  (void) obstack_finish (&irp);
  /* Default values of members are NULL and zero.  */
  memset (result, 0, size);
  return result;
}