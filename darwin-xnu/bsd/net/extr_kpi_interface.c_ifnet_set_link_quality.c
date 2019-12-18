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
typedef  int /*<<< orphan*/ * ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENXIO ; 
 int IFNET_LQM_MAX ; 
 int IFNET_LQM_MIN ; 
 int /*<<< orphan*/  if_lqm_update (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_is_attached (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

errno_t
ifnet_set_link_quality(ifnet_t ifp, int quality)
{
	errno_t err = 0;

	if (ifp == NULL || quality < IFNET_LQM_MIN || quality > IFNET_LQM_MAX) {
		err = EINVAL;
		goto done;
	}

	if (!ifnet_is_attached(ifp, 0)) {
		err = ENXIO;
		goto done;
	}

	if_lqm_update(ifp, quality, 0);

done:
	return (err);
}