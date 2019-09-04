#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* __bits; } ;
typedef  TYPE_1__ sigset_t ;

/* Variables and functions */
 int _NSIG ; 

int sigfillset(sigset_t *set)
{
#if ULONG_MAX == 0xffffffff
	set->__bits[0] = 0x7ffffffful;
	set->__bits[1] = 0xfffffffcul;
	if (_NSIG > 65) {
		set->__bits[2] = 0xfffffffful;
		set->__bits[3] = 0xfffffffful;
	}
#else
	set->__bits[0] = 0xfffffffc7ffffffful;
	if (_NSIG > 65) set->__bits[1] = 0xfffffffffffffffful;
#endif
	return 0;
}