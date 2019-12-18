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
struct packet_data {int frames; scalar_t__* pages; } ;
struct bio_vec {scalar_t__ bv_page; int bv_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CD_FRAMESIZE ; 
 int /*<<< orphan*/  KM_USER0 ; 
 int PAGE_SIZE ; 
 void* kmap_atomic (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,scalar_t__) ; 
 void* page_address (scalar_t__) ; 

__attribute__((used)) static void pkt_make_local_copy(struct packet_data *pkt, struct bio_vec *bvec)
{
	int f, p, offs;

	/* Copy all data to pkt->pages[] */
	p = 0;
	offs = 0;
	for (f = 0; f < pkt->frames; f++) {
		if (bvec[f].bv_page != pkt->pages[p]) {
			void *vfrom = kmap_atomic(bvec[f].bv_page, KM_USER0) + bvec[f].bv_offset;
			void *vto = page_address(pkt->pages[p]) + offs;
			memcpy(vto, vfrom, CD_FRAMESIZE);
			kunmap_atomic(vfrom, KM_USER0);
			bvec[f].bv_page = pkt->pages[p];
			bvec[f].bv_offset = offs;
		} else {
			BUG_ON(bvec[f].bv_offset != offs);
		}
		offs += CD_FRAMESIZE;
		if (offs >= PAGE_SIZE) {
			offs = 0;
			p++;
		}
	}
}