#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  size_t u16 ;
struct ipath_user_sdma_pkt {int naddr; TYPE_1__* addr; } ;
struct ipath_devdata {TYPE_2__* ipath_sdma_descq; } ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_4__ {int /*<<< orphan*/ * qw; } ;
struct TYPE_3__ {scalar_t__ length; scalar_t__ offset; scalar_t__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipath_sdma_make_desc0 (struct ipath_devdata*,int const,int const,unsigned int) ; 
 int /*<<< orphan*/  ipath_sdma_make_desc1 (int const) ; 
 int /*<<< orphan*/  ipath_sdma_make_first_desc0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_sdma_make_last_desc0 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipath_user_sdma_send_frag(struct ipath_devdata *dd,
				      struct ipath_user_sdma_pkt *pkt, int idx,
				      unsigned ofs, u16 tail)
{
	const u64 addr = (u64) pkt->addr[idx].addr +
		(u64) pkt->addr[idx].offset;
	const u64 dwlen = (u64) pkt->addr[idx].length / 4;
	__le64 *descqp;
	__le64 descq0;

	descqp = &dd->ipath_sdma_descq[tail].qw[0];

	descq0 = ipath_sdma_make_desc0(dd, addr, dwlen, ofs);
	if (idx == 0)
		descq0 = ipath_sdma_make_first_desc0(descq0);
	if (idx == pkt->naddr - 1)
		descq0 = ipath_sdma_make_last_desc0(descq0);

	descqp[0] = descq0;
	descqp[1] = ipath_sdma_make_desc1(addr);
}