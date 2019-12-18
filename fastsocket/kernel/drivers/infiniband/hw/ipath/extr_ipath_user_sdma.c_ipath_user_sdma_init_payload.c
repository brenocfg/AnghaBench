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
struct ipath_user_sdma_queue {int dummy; } ;
struct ipath_user_sdma_pkt {int /*<<< orphan*/  addr; } ;
struct ipath_devdata {int dummy; } ;
struct iovec {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ipath_user_sdma_coalesce (struct ipath_devdata const*,struct ipath_user_sdma_pkt*,struct iovec const*,unsigned long) ; 
 int ipath_user_sdma_pin_pkt (struct ipath_devdata const*,struct ipath_user_sdma_queue*,struct ipath_user_sdma_pkt*,struct iovec const*,unsigned long) ; 

__attribute__((used)) static int ipath_user_sdma_init_payload(const struct ipath_devdata *dd,
					struct ipath_user_sdma_queue *pq,
					struct ipath_user_sdma_pkt *pkt,
					const struct iovec *iov,
					unsigned long niov, int npages)
{
	int ret = 0;

	if (npages >= ARRAY_SIZE(pkt->addr))
		ret = ipath_user_sdma_coalesce(dd, pkt, iov, niov);
	else
		ret = ipath_user_sdma_pin_pkt(dd, pq, pkt, iov, niov);

	return ret;
}