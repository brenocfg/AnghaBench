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
 scalar_t__ CAP_ENDPTCTRL ; 
 int /*<<< orphan*/  ENDPTCTRL_RXE ; 
 int /*<<< orphan*/  ENDPTCTRL_TXE ; 
 int /*<<< orphan*/  hw_cwrite (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_ep_flush (int,int) ; 

__attribute__((used)) static int hw_ep_disable(int num, int dir)
{
	hw_ep_flush(num, dir);
	hw_cwrite(CAP_ENDPTCTRL + num * sizeof(u32),
		  dir ? ENDPTCTRL_TXE : ENDPTCTRL_RXE, 0);
	return 0;
}