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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  _SHIFTR (int,int,int) ; 
 int crand_next ; 

__attribute__((used)) static __inline__ u32 __card_rand()
{
	crand_next = (crand_next*0x41C64E6D)+12345;
	return _SHIFTR(crand_next,16,15);
}