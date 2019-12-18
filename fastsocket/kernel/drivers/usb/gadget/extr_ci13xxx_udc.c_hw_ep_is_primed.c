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
 int /*<<< orphan*/  CAP_ENDPTPRIME ; 
 int /*<<< orphan*/  CAP_ENDPTSTAT ; 
 int hw_cread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_ep_bit (int,int) ; 
 int test_bit (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int hw_ep_is_primed(int num, int dir)
{
	u32 reg = hw_cread(CAP_ENDPTPRIME, ~0) | hw_cread(CAP_ENDPTSTAT, ~0);

	return test_bit(hw_ep_bit(num, dir), (void *)&reg);
}