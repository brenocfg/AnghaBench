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
 int /*<<< orphan*/  RSL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X1 ; 
 int /*<<< orphan*/  X2 ; 

__attribute__((used)) static void rsem_AA1B(void)
{
	RSL(X1);
	RSL(X2); // this one should fail
}