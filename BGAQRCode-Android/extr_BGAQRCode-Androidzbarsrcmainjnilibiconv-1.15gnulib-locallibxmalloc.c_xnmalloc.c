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
 void* fixup_null_alloc (size_t) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  xalloc_die () ; 
 scalar_t__ xalloc_oversized (size_t,size_t) ; 

void *
xnmalloc (size_t nmemb, size_t size)
{
  size_t n;
  void *p;

  if (xalloc_oversized (nmemb, size))
    xalloc_die ();
  n = nmemb * size;
  p = malloc (n);
  if (p == NULL)
    p = fixup_null_alloc (n);
  return p;
}