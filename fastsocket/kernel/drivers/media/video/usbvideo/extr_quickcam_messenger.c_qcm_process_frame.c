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
typedef  int /*<<< orphan*/  u8 ;
struct uvd {int /*<<< orphan*/  dp; } ;
typedef  int __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  RingQueue_Enqueue (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int be16_to_cpu (int) ; 
 int cpu_to_be16 (int) ; 
 int /*<<< orphan*/ * marker ; 

__attribute__((used)) static int qcm_process_frame(struct uvd *uvd, u8 *cdata, int framelen)
{
	int datalen;
	int totaldata;
	struct framehdr {
		__be16 id;
		__be16 len;
	};
	struct framehdr *fhdr;

	totaldata = 0;
	while (framelen) {
		fhdr = (struct framehdr *) cdata;
		datalen = be16_to_cpu(fhdr->len);
		framelen -= 4;
		cdata += 4;

		if ((fhdr->id) == cpu_to_be16(0x8001)) {
			RingQueue_Enqueue(&uvd->dp, marker, 4);
			totaldata += 4;
			continue;
		}
		if ((fhdr->id & cpu_to_be16(0xFF00)) == cpu_to_be16(0x0200)) {
			RingQueue_Enqueue(&uvd->dp, cdata, datalen);
			totaldata += datalen;
		}
		framelen -= datalen;
		cdata += datalen;
	}
	return totaldata;
}