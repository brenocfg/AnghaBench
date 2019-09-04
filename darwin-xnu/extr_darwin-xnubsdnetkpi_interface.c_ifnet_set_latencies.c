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
struct ifnet {int dummy; } ;
struct if_latencies {int dummy; } ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ifnet_set_input_latencies (struct ifnet*,struct if_latencies*) ; 
 int /*<<< orphan*/  ifnet_set_output_latencies (struct ifnet*,struct if_latencies*,int /*<<< orphan*/ ) ; 

errno_t
ifnet_set_latencies(struct ifnet *ifp, struct if_latencies *output_lt,
    struct if_latencies *input_lt)
{
	if (ifp == NULL)
		return (EINVAL);

	if (output_lt != NULL)
		(void) ifnet_set_output_latencies(ifp, output_lt, FALSE);

	if (input_lt != NULL)
		(void) ifnet_set_input_latencies(ifp, input_lt);

	return (0);
}