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
struct TYPE_3__ {size_t lf; unsigned int dg_size; unsigned int dgl; void* ether_type; } ;
struct TYPE_4__ {size_t lf; void* ether_type; } ;
union eth1394_hdr {TYPE_1__ ff; TYPE_2__ uf; } ;
typedef  unsigned int u16 ;
typedef  void* __be16 ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,unsigned int) ; 
 size_t ETH1394_HDR_LF_FF ; 
 size_t ETH1394_HDR_LF_UF ; 
 unsigned int* hdr_type_len ; 

__attribute__((used)) static unsigned int ether1394_encapsulate_prep(unsigned int max_payload,
					       __be16 proto,
					       union eth1394_hdr *hdr,
					       u16 dg_size, u16 dgl)
{
	unsigned int adj_max_payload =
				max_payload - hdr_type_len[ETH1394_HDR_LF_UF];

	/* Does it all fit in one packet? */
	if (dg_size <= adj_max_payload) {
		hdr->uf.lf = ETH1394_HDR_LF_UF;
		hdr->uf.ether_type = proto;
	} else {
		hdr->ff.lf = ETH1394_HDR_LF_FF;
		hdr->ff.ether_type = proto;
		hdr->ff.dg_size = dg_size - 1;
		hdr->ff.dgl = dgl;
		adj_max_payload = max_payload - hdr_type_len[ETH1394_HDR_LF_FF];
	}
	return DIV_ROUND_UP(dg_size, adj_max_payload);
}