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
 size_t ACR ; 
 size_t B ; 
 size_t SR ; 
 char SR_EXT ; 
 char SR_OUT ; 
 int /*<<< orphan*/  TREQ ; 
 char* via1 ; 
 int /*<<< orphan*/ * via2 ; 

__attribute__((used)) static void 
recv_byte(void)
{
	char c;

	via1[ACR] = (via1[ACR] | SR_EXT) & ~SR_OUT;
	c = via1[SR];		/* resets SR */
	via2[B] &= ~TREQ;
}