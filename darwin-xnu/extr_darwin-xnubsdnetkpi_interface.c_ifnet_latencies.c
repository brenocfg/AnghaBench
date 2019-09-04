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
struct if_latencies {int dummy; } ;
struct ifnet {struct if_latencies if_input_lt; struct if_latencies if_output_lt; } ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 

errno_t
ifnet_latencies(struct ifnet *ifp, struct if_latencies *output_lt,
    struct if_latencies *input_lt)
{
	if (ifp == NULL)
		return (EINVAL);

	if (output_lt != NULL)
		*output_lt = ifp->if_output_lt;
	if (input_lt != NULL)
		*input_lt = ifp->if_input_lt;

	return (0);
}