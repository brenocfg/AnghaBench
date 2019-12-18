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
struct ecb {int dummy; } ;
struct aha1740_hostdata {scalar_t__ ecb; scalar_t__ ecb_dma_addr; } ;
struct Scsi_Host {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 struct aha1740_hostdata* HOSTDATA (struct Scsi_Host*) ; 

__attribute__((used)) static inline struct ecb *ecb_dma_to_cpu (struct Scsi_Host *host,
					  dma_addr_t dma)
{
	struct aha1740_hostdata *hdata = HOSTDATA (host);
	dma_addr_t offset;

	offset = dma - hdata->ecb_dma_addr;

	return (struct ecb *)(((char *) hdata->ecb) + (unsigned int) offset);
}