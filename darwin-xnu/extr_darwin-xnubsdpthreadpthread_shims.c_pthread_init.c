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
struct TYPE_2__ {int /*<<< orphan*/  (* pthread_init ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*) ; 
 TYPE_1__* pthread_functions ; 
 int /*<<< orphan*/  stub1 () ; 

void
pthread_init(void)
{
	if (!pthread_functions) {
		panic("pthread kernel extension not loaded (function table is NULL).");
	}
	pthread_functions->pthread_init();
}