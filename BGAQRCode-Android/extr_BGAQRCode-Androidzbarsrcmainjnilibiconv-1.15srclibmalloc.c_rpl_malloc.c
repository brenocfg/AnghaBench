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
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  errno ; 
 void* malloc (size_t) ; 

void *
rpl_malloc (size_t n)
{
  void *result;

#if NEED_MALLOC_GNU
  if (n == 0)
    n = 1;
#endif

  result = malloc (n);

#if !HAVE_MALLOC_POSIX
  if (result == NULL)
    errno = ENOMEM;
#endif

  return result;
}