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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  jsf_outl (unsigned long,int) ; 
 int /*<<< orphan*/  jsf_wait (unsigned long) ; 

__attribute__((used)) static void jsf_write4(unsigned long fa, u32 data) {

	jsf_outl(fa, 0xAAAAAAAA);		/* Unlock 1 Write 1 */
	jsf_outl(fa, 0x55555555);		/* Unlock 1 Write 2 */
	jsf_outl(fa, 0xA0A0A0A0);		/* Byte Program */
	jsf_outl(fa, data);

	jsf_wait(fa);
}