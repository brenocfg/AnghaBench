#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* base_mem; } ;
typedef  TYPE_1__ T3Memory ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void T3MemoryDeInit(T3Memory * mem)
{
   free(mem->base_mem);
   free(mem);
}