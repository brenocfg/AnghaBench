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
 int SR_CTRL ; 
 int /*<<< orphan*/  TREQ ; 
 int* via1 ; 
 int /*<<< orphan*/ * via2 ; 

__attribute__((used)) static void 
send_byte(int x)
{
	via1[ACR] |= SR_CTRL;
	via1[SR] = x;
	via2[B] &= ~TREQ;		/* assert TREQ */
}