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
typedef  void uint8_t ;
typedef  int uint32_t ;
struct scb {int sg_list_busaddr; scalar_t__ sg_list; } ;
struct ahd_softc {int dummy; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int ahd_sg_size (struct ahd_softc*) ; 

__attribute__((used)) static void *
ahd_sg_bus_to_virt(struct ahd_softc *ahd, struct scb *scb, uint32_t sg_busaddr)
{
	dma_addr_t sg_offset;

	/* sg_list_phys points to entry 1, not 0 */
	sg_offset = sg_busaddr - (scb->sg_list_busaddr - ahd_sg_size(ahd));
	return ((uint8_t *)scb->sg_list + sg_offset);
}