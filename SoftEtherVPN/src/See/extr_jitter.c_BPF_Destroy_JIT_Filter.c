#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* Function; struct TYPE_5__* mem; } ;
typedef  TYPE_1__ JIT_BPF_Filter ;

/* Variables and functions */
 int /*<<< orphan*/  ExFreePool (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void BPF_Destroy_JIT_Filter(JIT_BPF_Filter *Filter){
	
#ifdef NTKERNEL
	ExFreePool(Filter->mem);
	ExFreePool(Filter->Function);
	ExFreePool(Filter);
#else
	free(Filter->mem);
	free(Filter->Function);
	free(Filter);
#endif

}