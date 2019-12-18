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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct hpsb_packet {void** data; int /*<<< orphan*/  node_id; struct hpsb_host* host; } ;
struct hpsb_host {int dummy; } ;
typedef  void* quadlet_t ;
typedef  int /*<<< orphan*/  nodeid_t ;

/* Variables and functions */
#define  EXTCODE_FETCH_ADD 129 
#define  EXTCODE_LITTLE_ADD 128 
 int /*<<< orphan*/  fill_async_lock (struct hpsb_packet*,int /*<<< orphan*/ ,int,int) ; 
 struct hpsb_packet* hpsb_alloc_packet (int) ; 
 int /*<<< orphan*/  hpsb_free_packet (struct hpsb_packet*) ; 
 scalar_t__ hpsb_get_tlabel (struct hpsb_packet*) ; 

struct hpsb_packet *hpsb_make_lockpacket(struct hpsb_host *host, nodeid_t node,
					 u64 addr, int extcode,
					 quadlet_t * data, quadlet_t arg)
{
	struct hpsb_packet *p;
	u32 length;

	p = hpsb_alloc_packet(8);
	if (!p)
		return NULL;

	p->host = host;
	p->node_id = node;
	if (hpsb_get_tlabel(p)) {
		hpsb_free_packet(p);
		return NULL;
	}

	switch (extcode) {
	case EXTCODE_FETCH_ADD:
	case EXTCODE_LITTLE_ADD:
		length = 4;
		if (data)
			p->data[0] = *data;
		break;
	default:
		length = 8;
		if (data) {
			p->data[0] = arg;
			p->data[1] = *data;
		}
		break;
	}
	fill_async_lock(p, addr, extcode, length);

	return p;
}