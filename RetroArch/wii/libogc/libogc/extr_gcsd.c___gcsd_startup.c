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

/* Variables and functions */
 int __gcsd_init ; 
 int __gcsd_isInserted (int) ; 
 int /*<<< orphan*/  sdgecko_initBufferPool () ; 
 int /*<<< orphan*/  sdgecko_initIODefault () ; 

__attribute__((used)) static bool __gcsd_startup(int n)
{
	if(__gcsd_init == 1)
		return __gcsd_isInserted(n);
	sdgecko_initBufferPool();
	sdgecko_initIODefault();
	__gcsd_init = 1;
	return __gcsd_isInserted(n);
}