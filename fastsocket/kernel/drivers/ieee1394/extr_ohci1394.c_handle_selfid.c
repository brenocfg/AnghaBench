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
struct ti_ohci {int* selfid_buf_cpu; scalar_t__ selfid_swap; int /*<<< orphan*/  self_id_errors; } ;
struct hpsb_host {int dummy; } ;
typedef  int quadlet_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBGMSG (char*,...) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  OHCI1394_MAX_SELF_ID_ERRORS ; 
 int /*<<< orphan*/  OHCI1394_SelfIDCount ; 
 int /*<<< orphan*/  PRINT (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  hpsb_selfid_received (struct hpsb_host*,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int) ; 
 int reg_read (struct ti_ohci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_phy_reg_mask (struct ti_ohci*,int,int) ; 

__attribute__((used)) static void handle_selfid(struct ti_ohci *ohci, struct hpsb_host *host,
				int phyid, int isroot)
{
	quadlet_t *q = ohci->selfid_buf_cpu;
	quadlet_t self_id_count=reg_read(ohci, OHCI1394_SelfIDCount);
	size_t size;
	quadlet_t q0, q1;

	/* Check status of self-id reception */

	if (ohci->selfid_swap)
		q0 = le32_to_cpu(q[0]);
	else
		q0 = q[0];

	if ((self_id_count & 0x80000000) ||
	    ((self_id_count & 0x00FF0000) != (q0 & 0x00FF0000))) {
		PRINT(KERN_ERR,
		      "Error in reception of SelfID packets [0x%08x/0x%08x] (count: %d)",
		      self_id_count, q0, ohci->self_id_errors);

		/* Tip by James Goodwin <jamesg@Filanet.com>:
		 * We had an error, generate another bus reset in response.  */
		if (ohci->self_id_errors<OHCI1394_MAX_SELF_ID_ERRORS) {
			set_phy_reg_mask (ohci, 1, 0x40);
			ohci->self_id_errors++;
		} else {
			PRINT(KERN_ERR,
			      "Too many errors on SelfID error reception, giving up!");
		}
		return;
	}

	/* SelfID Ok, reset error counter. */
	ohci->self_id_errors = 0;

	size = ((self_id_count & 0x00001FFC) >> 2) - 1;
	q++;

	while (size > 0) {
		if (ohci->selfid_swap) {
			q0 = le32_to_cpu(q[0]);
			q1 = le32_to_cpu(q[1]);
		} else {
			q0 = q[0];
			q1 = q[1];
		}

		if (q0 == ~q1) {
			DBGMSG ("SelfID packet 0x%x received", q0);
			hpsb_selfid_received(host, cpu_to_be32(q0));
			if (((q0 & 0x3f000000) >> 24) == phyid)
				DBGMSG ("SelfID for this node is 0x%08x", q0);
		} else {
			PRINT(KERN_ERR,
			      "SelfID is inconsistent [0x%08x/0x%08x]", q0, q1);
		}
		q += 2;
		size -= 2;
	}

	DBGMSG("SelfID complete");

	return;
}