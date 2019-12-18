#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ iov_len; int /*<<< orphan*/ * iov_base; } ;
struct TYPE_4__ {scalar_t__ iov_len; int /*<<< orphan*/ * iov_base; } ;
struct TYPE_6__ {TYPE_2__ cga_pubkey; TYPE_1__ cga_privkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  M_IP6CGA ; 
 TYPE_3__ in6_cga ; 
 int /*<<< orphan*/  in6_cga_node_lock_assert (int /*<<< orphan*/ ) ; 

int
in6_cga_stop(void)
{
	in6_cga_node_lock_assert(LCK_MTX_ASSERT_OWNED);

	if (in6_cga.cga_privkey.iov_base != NULL) {
		FREE(in6_cga.cga_privkey.iov_base, M_IP6CGA);
		in6_cga.cga_privkey.iov_base = NULL;
		in6_cga.cga_privkey.iov_len = 0;
	}

	if (in6_cga.cga_pubkey.iov_base != NULL) {
		FREE(in6_cga.cga_pubkey.iov_base, M_IP6CGA);
		in6_cga.cga_pubkey.iov_base = NULL;
		in6_cga.cga_pubkey.iov_len = 0;
	}

	return (0);
}