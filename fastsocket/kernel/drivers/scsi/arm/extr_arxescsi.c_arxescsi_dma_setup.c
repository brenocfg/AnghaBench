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
struct scsi_pointer {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  fasdmatype_t ;
typedef  int /*<<< orphan*/  fasdmadir_t ;

/* Variables and functions */
 int /*<<< orphan*/  fasdma_pseudo ; 

__attribute__((used)) static fasdmatype_t
arxescsi_dma_setup(struct Scsi_Host *host, struct scsi_pointer *SCp,
		       fasdmadir_t direction, fasdmatype_t min_type)
{
	/*
	 * We don't do real DMA
	 */
	return fasdma_pseudo;
}