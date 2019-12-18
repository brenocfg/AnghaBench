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
struct macio_dev {int dummy; } ;
struct fsc_state {int /*<<< orphan*/  dma_cmd_space; scalar_t__ dma; scalar_t__ regs; int /*<<< orphan*/  intr; struct Scsi_Host* host; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct fsc_state*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 scalar_t__ macio_get_drvdata (struct macio_dev*) ; 
 int /*<<< orphan*/  macio_release_resources (struct macio_dev*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 

__attribute__((used)) static int mac53c94_remove(struct macio_dev *mdev)
{
	struct fsc_state *fp = (struct fsc_state *)macio_get_drvdata(mdev);
	struct Scsi_Host *host = fp->host;

	scsi_remove_host(host);

	free_irq(fp->intr, fp);

	if (fp->regs)
		iounmap(fp->regs);
	if (fp->dma)
		iounmap(fp->dma);
	kfree(fp->dma_cmd_space);

	scsi_host_put(host);

	macio_release_resources(mdev);

	return 0;
}