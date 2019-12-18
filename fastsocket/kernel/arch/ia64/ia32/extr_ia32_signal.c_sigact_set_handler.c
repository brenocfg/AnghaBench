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
struct TYPE_2__ {void* sa_handler; } ;
struct k_sigaction {TYPE_1__ sa; } ;
typedef  void* __sighandler_t ;

/* Variables and functions */
 scalar_t__ A (int) ; 

__attribute__((used)) static inline void
sigact_set_handler (struct k_sigaction *sa, unsigned int handler, unsigned int restorer)
{
	if (handler + 1 <= 2)
		/* SIG_DFL, SIG_IGN, or SIG_ERR: must sign-extend to 64-bits */
		sa->sa.sa_handler = (__sighandler_t) A((int) handler);
	else
		sa->sa.sa_handler = (__sighandler_t) (((unsigned long) restorer << 32) | handler);
}