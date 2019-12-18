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
struct hpsb_packet {int /*<<< orphan*/  type; int /*<<< orphan*/  generation; struct hpsb_host* host; } ;
struct hpsb_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_hpsb_generation (struct hpsb_host*) ; 
 struct hpsb_packet* hpsb_alloc_packet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpsb_async ; 

__attribute__((used)) static struct hpsb_packet *ether1394_alloc_common_packet(struct hpsb_host *host)
{
	struct hpsb_packet *p;

	p = hpsb_alloc_packet(0);
	if (p) {
		p->host = host;
		p->generation = get_hpsb_generation(host);
		p->type = hpsb_async;
	}
	return p;
}