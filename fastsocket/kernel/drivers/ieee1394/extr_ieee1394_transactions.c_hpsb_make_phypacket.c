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
struct hpsb_packet {struct hpsb_host* host; } ;
struct hpsb_host {int dummy; } ;
typedef  int /*<<< orphan*/  quadlet_t ;

/* Variables and functions */
 int /*<<< orphan*/  fill_phy_packet (struct hpsb_packet*,int /*<<< orphan*/ ) ; 
 struct hpsb_packet* hpsb_alloc_packet (int /*<<< orphan*/ ) ; 

struct hpsb_packet *hpsb_make_phypacket(struct hpsb_host *host, quadlet_t data)
{
	struct hpsb_packet *p;

	p = hpsb_alloc_packet(0);
	if (!p)
		return NULL;

	p->host = host;
	fill_phy_packet(p, data);

	return p;
}