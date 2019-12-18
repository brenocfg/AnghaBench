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
typedef  int /*<<< orphan*/  PTR ;

/* Variables and functions */
 int /*<<< orphan*/  malloc (size_t) ; 
 int /*<<< orphan*/  realloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  xmalloc_failed (size_t) ; 

PTR
xrealloc (PTR oldmem, size_t size)
{
  PTR newmem;

  if (size == 0)
    size = 1;
  if (!oldmem)
    newmem = malloc (size);
  else
    newmem = realloc (oldmem, size);
  if (!newmem)
    xmalloc_failed (size);

  return (newmem);
}