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
typedef  int /*<<< orphan*/  ALvoid ;

/* Variables and functions */
 int /*<<< orphan*/  ALUT_ERROR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  _alutSetError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int) ; 

ALvoid *_alutMalloc(size_t size)
{
  ALvoid *ptr = malloc(size == 0 ? 1 : size);

  if (ptr == NULL)
  {
    _alutSetError(ALUT_ERROR_OUT_OF_MEMORY);
  }
  return ptr;
}