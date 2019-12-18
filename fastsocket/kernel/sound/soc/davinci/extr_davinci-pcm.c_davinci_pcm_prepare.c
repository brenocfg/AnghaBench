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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct edmacc_param {int dummy; } ;
struct davinci_runtime_data {int /*<<< orphan*/  master_lch; int /*<<< orphan*/  slave_lch; scalar_t__ period; } ;
struct TYPE_2__ {struct davinci_runtime_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  davinci_pcm_enqueue_dma (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  edma_read_slot (int /*<<< orphan*/ ,struct edmacc_param*) ; 
 int /*<<< orphan*/  edma_write_slot (int /*<<< orphan*/ ,struct edmacc_param*) ; 

__attribute__((used)) static int davinci_pcm_prepare(struct snd_pcm_substream *substream)
{
	struct davinci_runtime_data *prtd = substream->runtime->private_data;
	struct edmacc_param temp;

	prtd->period = 0;
	davinci_pcm_enqueue_dma(substream);

	/* Copy self-linked parameter RAM entry into master channel */
	edma_read_slot(prtd->slave_lch, &temp);
	edma_write_slot(prtd->master_lch, &temp);
	davinci_pcm_enqueue_dma(substream);

	return 0;
}