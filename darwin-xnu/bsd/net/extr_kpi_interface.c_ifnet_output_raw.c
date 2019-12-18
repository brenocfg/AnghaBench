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
typedef  int /*<<< orphan*/  protocol_family_t ;
typedef  int /*<<< orphan*/ * mbuf_t ;
typedef  int /*<<< orphan*/ * ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  dlil_output (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbuf_freem_list (int /*<<< orphan*/ *) ; 

errno_t
ifnet_output_raw(ifnet_t interface, protocol_family_t protocol_family, mbuf_t m)
{
	if (interface == NULL || m == NULL) {
		if (m != NULL)
			mbuf_freem_list(m);
		return (EINVAL);
	}
	return (dlil_output(interface, protocol_family, m, NULL, NULL, 1, NULL));
}