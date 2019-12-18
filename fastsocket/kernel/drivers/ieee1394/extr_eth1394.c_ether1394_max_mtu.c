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
typedef  union eth1394_hdr {int dummy; } eth1394_hdr ;
struct TYPE_2__ {int max_rec; } ;
struct hpsb_host {TYPE_1__ csr; } ;

/* Variables and functions */
 int ETHER1394_GASP_OVERHEAD ; 

__attribute__((used)) static inline int ether1394_max_mtu(struct hpsb_host* host)
{
	return (1 << (host->csr.max_rec + 1))
			- sizeof(union eth1394_hdr) - ETHER1394_GASP_OVERHEAD;
}