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
struct if_bandwidths {int dummy; } ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ifnet_set_input_bandwidths (struct ifnet*,struct if_bandwidths*) ; 
 int /*<<< orphan*/  ifnet_set_output_bandwidths (struct ifnet*,struct if_bandwidths*,int /*<<< orphan*/ ) ; 

errno_t
ifnet_set_bandwidths(struct ifnet *ifp, struct if_bandwidths *output_bw,
    struct if_bandwidths *input_bw)
{
	if (ifp == NULL)
		return (EINVAL);

	/* set input values first (if any), as output values depend on them */
	if (input_bw != NULL)
		(void) ifnet_set_input_bandwidths(ifp, input_bw);

	if (output_bw != NULL)
		(void) ifnet_set_output_bandwidths(ifp, output_bw, FALSE);

	return (0);
}