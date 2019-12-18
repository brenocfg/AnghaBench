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
 int /*<<< orphan*/  conversion_obstack ; 
 int conversion_obstack_initialized ; 
 int /*<<< orphan*/  gcc_obstack_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 void* obstack_alloc (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void *
conversion_obstack_alloc (size_t n)
{
  void *p;
  if (!conversion_obstack_initialized)
    {
      gcc_obstack_init (&conversion_obstack);
      conversion_obstack_initialized = true;
    }
  p = obstack_alloc (&conversion_obstack, n);
  memset (p, 0, n);
  return p;
}