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
struct TYPE_2__ {uintptr_t CANARY; } ;

/* Variables and functions */
 TYPE_1__* __pthread_self () ; 
 uintptr_t __stack_chk_guard ; 
 int /*<<< orphan*/  memcpy (uintptr_t*,void*,int) ; 

void __init_ssp(void *entropy)
{
	if (entropy) memcpy(&__stack_chk_guard, entropy, sizeof(uintptr_t));
	else __stack_chk_guard = (uintptr_t)&__stack_chk_guard * 1103515245;

	__pthread_self()->CANARY = __stack_chk_guard;
}