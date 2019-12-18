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
typedef  int u64 ;
struct mem_ctl_info {int /*<<< orphan*/  dev; struct csrow_info* csrows; struct cell_edac_priv* pvt_info; } ;
struct csrow_info {scalar_t__ first_page; } ;
struct cell_edac_priv {int chanmask; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  edac_mc_handle_ce (struct mem_ctl_info*,scalar_t__,unsigned long,unsigned long,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static void cell_edac_count_ce(struct mem_ctl_info *mci, int chan, u64 ar)
{
	struct cell_edac_priv		*priv = mci->pvt_info;
	struct csrow_info		*csrow = &mci->csrows[0];
	unsigned long			address, pfn, offset, syndrome;

	dev_dbg(mci->dev, "ECC CE err on node %d, channel %d, ar = 0x%016llx\n",
		priv->node, chan, ar);

	/* Address decoding is likely a bit bogus, to dbl check */
	address = (ar & 0xffffffffe0000000ul) >> 29;
	if (priv->chanmask == 0x3)
		address = (address << 1) | chan;
	pfn = address >> PAGE_SHIFT;
	offset = address & ~PAGE_MASK;
	syndrome = (ar & 0x000000001fe00000ul) >> 21;

	/* TODO: Decoding of the error addresss */
	edac_mc_handle_ce(mci, csrow->first_page + pfn, offset,
			  syndrome, 0, chan, "");
}