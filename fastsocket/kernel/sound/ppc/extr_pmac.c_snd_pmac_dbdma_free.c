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
struct snd_pmac {TYPE_1__* pdev; } ;
struct pmac_dbdma {int size; int /*<<< orphan*/  dma_base; scalar_t__ space; } ;
struct dbdma_cmd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,unsigned int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_pmac_dbdma_free(struct snd_pmac *chip, struct pmac_dbdma *rec)
{
	if (rec->space) {
		unsigned int rsize = sizeof(struct dbdma_cmd) * (rec->size + 1);

		dma_free_coherent(&chip->pdev->dev, rsize, rec->space, rec->dma_base);
	}
}