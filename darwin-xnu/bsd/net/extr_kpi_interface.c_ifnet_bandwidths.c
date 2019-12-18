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
struct if_bandwidths {int dummy; } ;
struct ifnet {struct if_bandwidths if_input_bw; struct if_bandwidths if_output_bw; } ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 

errno_t
ifnet_bandwidths(struct ifnet *ifp, struct if_bandwidths *output_bw,
    struct if_bandwidths *input_bw)
{
	if (ifp == NULL)
		return (EINVAL);

	if (output_bw != NULL)
		*output_bw = ifp->if_output_bw;
	if (input_bw != NULL)
		*input_bw = ifp->if_input_bw;

	return (0);
}