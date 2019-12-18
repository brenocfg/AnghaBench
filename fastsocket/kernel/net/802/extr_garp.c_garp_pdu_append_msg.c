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
typedef  void* u8 ;
struct garp_msg_hdr {void* attrtype; } ;
struct garp_applicant {int /*<<< orphan*/  pdu; } ;
struct TYPE_2__ {void* cur_type; } ;

/* Variables and functions */
 scalar_t__ __skb_put (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* garp_cb (int /*<<< orphan*/ ) ; 
 int skb_tailroom (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int garp_pdu_append_msg(struct garp_applicant *app, u8 attrtype)
{
	struct garp_msg_hdr *gm;

	if (skb_tailroom(app->pdu) < sizeof(*gm))
		return -1;
	gm = (struct garp_msg_hdr *)__skb_put(app->pdu, sizeof(*gm));
	gm->attrtype = attrtype;
	garp_cb(app->pdu)->cur_type = attrtype;
	return 0;
}