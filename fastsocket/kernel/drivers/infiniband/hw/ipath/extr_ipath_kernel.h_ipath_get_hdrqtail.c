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
typedef  scalar_t__ u32 ;
struct ipath_portdata {int port_head; scalar_t__ port_seq_cnt; scalar_t__ port_rcvhdrq; struct ipath_devdata* port_dd; } ;
struct ipath_devdata {int ipath_flags; int ipath_rhf_offset; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int IPATH_NODMA_RTAIL ; 
 scalar_t__ ipath_get_rcvhdrtail (struct ipath_portdata const*) ; 
 scalar_t__ ipath_hdrget_seq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u32 ipath_get_hdrqtail(const struct ipath_portdata *pd)
{
	const struct ipath_devdata *dd = pd->port_dd;
	u32 hdrqtail;

	if (dd->ipath_flags & IPATH_NODMA_RTAIL) {
		__le32 *rhf_addr;
		u32 seq;

		rhf_addr = (__le32 *) pd->port_rcvhdrq +
			pd->port_head + dd->ipath_rhf_offset;
		seq = ipath_hdrget_seq(rhf_addr);
		hdrqtail = pd->port_head;
		if (seq == pd->port_seq_cnt)
			hdrqtail++;
	} else
		hdrqtail = ipath_get_rcvhdrtail(pd);

	return hdrqtail;
}