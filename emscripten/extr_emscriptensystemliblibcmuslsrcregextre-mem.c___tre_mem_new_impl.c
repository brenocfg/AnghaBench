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
typedef  int /*<<< orphan*/ * tre_mem_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * xcalloc (int,int) ; 

tre_mem_t
tre_mem_new_impl(int provided, void *provided_block)
{
  tre_mem_t mem;
  if (provided)
    {
      mem = provided_block;
      memset(mem, 0, sizeof(*mem));
    }
  else
    mem = xcalloc(1, sizeof(*mem));
  if (mem == NULL)
    return NULL;
  return mem;
}