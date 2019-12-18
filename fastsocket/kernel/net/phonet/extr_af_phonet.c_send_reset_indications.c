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
typedef  int u8 ;
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct phonethdr {int pn_robj; int /*<<< orphan*/  pn_rdev; int /*<<< orphan*/  pn_sdev; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  PN_COMMGR ; 
 struct phonethdr* pn_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  pn_object (int /*<<< orphan*/ ,int) ; 
 int pn_raw_send (int const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_reset_indications(struct sk_buff *rskb)
{
	struct phonethdr *oph = pn_hdr(rskb);
	static const u8 data[4] = {
		0x00 /* trans ID */, 0x10 /* subscribe msg */,
		0x00 /* subscription count */, 0x00 /* dummy */
	};

	return pn_raw_send(data, sizeof(data), rskb->dev,
				pn_object(oph->pn_sdev, 0x00),
				pn_object(oph->pn_rdev, oph->pn_robj),
				PN_COMMGR);
}