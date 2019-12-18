#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct niu {int port; TYPE_1__* parent; } ;
struct TYPE_2__ {scalar_t__ plat_type; } ;

/* Variables and functions */
 int ATLAS_P0_P1_DFIFO_ENTRIES ; 
 int ATLAS_P2_P3_DFIFO_ENTRIES ; 
 int /*<<< orphan*/  IPP_BAD_CS_CNT ; 
 int /*<<< orphan*/  IPP_CFIG ; 
 int IPP_CFIG_CKSUM_EN ; 
 int IPP_CFIG_DFIFO_ECC_EN ; 
 int IPP_CFIG_DROP_BAD_CRC ; 
 int IPP_CFIG_IPP_ENABLE ; 
 int IPP_CFIG_IP_MAX_PKT ; 
 int IPP_CFIG_IP_MAX_PKT_SHIFT ; 
 int /*<<< orphan*/  IPP_ECC ; 
 int /*<<< orphan*/  IPP_INT_STAT ; 
 int /*<<< orphan*/  IPP_MSK ; 
 int IPP_MSK_ALL ; 
 int /*<<< orphan*/  IPP_PKT_DIS ; 
 int NIU_DFIFO_ENTRIES ; 
 scalar_t__ PLAT_TYPE_NIU ; 
 int /*<<< orphan*/  niu_ipp_read (struct niu*,int,int*) ; 
 int niu_ipp_reset (struct niu*) ; 
 int /*<<< orphan*/  niu_ipp_write (struct niu*,int,int*) ; 
 int nr64_ipp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw64_ipp (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int niu_init_ipp(struct niu *np)
{
	u64 data[5], rbuf[5], val;
	int i, max, err;

	if (np->parent->plat_type != PLAT_TYPE_NIU) {
		if (np->port == 0 || np->port == 1)
			max = ATLAS_P0_P1_DFIFO_ENTRIES;
		else
			max = ATLAS_P2_P3_DFIFO_ENTRIES;
	} else
		max = NIU_DFIFO_ENTRIES;

	data[0] = 0;
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;
	data[4] = 0;

	for (i = 0; i < max; i++) {
		niu_ipp_write(np, i, data);
		niu_ipp_read(np, i, rbuf);
	}

	(void) nr64_ipp(IPP_INT_STAT);
	(void) nr64_ipp(IPP_INT_STAT);

	err = niu_ipp_reset(np);
	if (err)
		return err;

	(void) nr64_ipp(IPP_PKT_DIS);
	(void) nr64_ipp(IPP_BAD_CS_CNT);
	(void) nr64_ipp(IPP_ECC);

	(void) nr64_ipp(IPP_INT_STAT);

	nw64_ipp(IPP_MSK, ~IPP_MSK_ALL);

	val = nr64_ipp(IPP_CFIG);
	val &= ~IPP_CFIG_IP_MAX_PKT;
	val |= (IPP_CFIG_IPP_ENABLE |
		IPP_CFIG_DFIFO_ECC_EN |
		IPP_CFIG_DROP_BAD_CRC |
		IPP_CFIG_CKSUM_EN |
		(0x1ffff << IPP_CFIG_IP_MAX_PKT_SHIFT));
	nw64_ipp(IPP_CFIG, val);

	return 0;
}