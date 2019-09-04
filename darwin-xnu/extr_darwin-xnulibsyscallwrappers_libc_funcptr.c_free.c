#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void (* free ) (void*) ;} ;

/* Variables and functions */
 TYPE_1__* _libkernel_functions ; 
 void stub1 (void*) ; 

__attribute__((visibility("hidden")))
void
free(void *ptr)
{
	return _libkernel_functions->free(ptr);
}