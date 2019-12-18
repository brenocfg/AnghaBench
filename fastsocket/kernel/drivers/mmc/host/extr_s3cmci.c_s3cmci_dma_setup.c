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
struct s3cmci_host {int /*<<< orphan*/  dma; scalar_t__ sdidata; TYPE_1__* mem; } ;
typedef  enum s3c2410_dmasrc { ____Placeholder_s3c2410_dmasrc } s3c2410_dmasrc ;
struct TYPE_2__ {scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C2410_DMAF_AUTOSTART ; 
 int /*<<< orphan*/  s3c2410_dma_config (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s3c2410_dma_devconfig (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  s3c2410_dma_set_buffdone_fn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c2410_dma_setflags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3cmci_dma_done_callback ; 

__attribute__((used)) static void s3cmci_dma_setup(struct s3cmci_host *host,
			     enum s3c2410_dmasrc source)
{
	static enum s3c2410_dmasrc last_source = -1;
	static int setup_ok;

	if (last_source == source)
		return;

	last_source = source;

	s3c2410_dma_devconfig(host->dma, source,
			      host->mem->start + host->sdidata);

	if (!setup_ok) {
		s3c2410_dma_config(host->dma, 4);
		s3c2410_dma_set_buffdone_fn(host->dma,
					    s3cmci_dma_done_callback);
		s3c2410_dma_setflags(host->dma, S3C2410_DMAF_AUTOSTART);
		setup_ok = 1;
	}
}