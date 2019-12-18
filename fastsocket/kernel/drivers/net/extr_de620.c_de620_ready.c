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
struct net_device {int dummy; } ;
typedef  int byte ;

/* Variables and functions */
 int READY ; 
 int /*<<< orphan*/  STATUS_PORT ; 
 int inb (int /*<<< orphan*/ ) ; 
 short tot_cnt ; 

__attribute__((used)) static inline byte
de620_ready(struct net_device *dev)
{
	byte value;
	register short int cnt = 0;

	while ((((value = inb(STATUS_PORT)) & READY) == 0) && (cnt <= 1000))
		++cnt;

#ifdef COUNT_LOOPS
	tot_cnt += cnt;
#endif
	return value & 0xf0; /* nibble */
}