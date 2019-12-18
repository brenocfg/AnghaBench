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
struct TYPE_3__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ poll_table ;

/* Variables and functions */
 int /*<<< orphan*/  POLLEX_SET ; 
 int /*<<< orphan*/  POLLIN_SET ; 
 int /*<<< orphan*/  POLLOUT_SET ; 

__attribute__((used)) static inline void wait_key_set(poll_table *wait, unsigned long in,
				unsigned long out, unsigned long bit)
{
	if (wait) {
		wait->key = POLLEX_SET;
		if (in & bit)
			wait->key |= POLLIN_SET;
		if (out & bit)
			wait->key |= POLLOUT_SET;
	}
}