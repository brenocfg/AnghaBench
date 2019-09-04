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
 void* malloc (size_t) ; 
 int /*<<< orphan*/  xalloc_die () ; 

__attribute__((used)) static void *
fixup_null_alloc (size_t n)
{
  void *p;

  p = NULL;
  if (n == 0)
    p = malloc ((size_t) 1);
  if (p == NULL)
    xalloc_die ();
  return p;
}