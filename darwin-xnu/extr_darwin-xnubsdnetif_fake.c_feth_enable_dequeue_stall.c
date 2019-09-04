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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  ifnet_t ;

/* Variables and functions */
 int ifnet_disable_output (int /*<<< orphan*/ ) ; 
 int ifnet_enable_output (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
feth_enable_dequeue_stall(ifnet_t ifp, uint32_t enable)
{
	int error;

	if (enable != 0)
		error = ifnet_disable_output(ifp);
	else
		error = ifnet_enable_output(ifp);

	return (error);
}