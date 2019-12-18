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
struct TYPE_3__ {scalar_t__ mbase; } ;
typedef  TYPE_1__ avmcard ;

/* Variables and functions */
 scalar_t__ DOORBELL ; 
 int c4inmeml (scalar_t__) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static inline int wait_for_doorbell(avmcard *card, unsigned long t)
{
	unsigned long stop;

	stop = jiffies + t;
	while (c4inmeml(card->mbase+DOORBELL) != 0xffffffff) {
		if (!time_before(jiffies, stop))
			return -1;
		mb();
	}
	return 0;
}