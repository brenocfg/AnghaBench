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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct davinci_runtime_data* private_data; } ;
struct davinci_runtime_data {int /*<<< orphan*/  master_lch; int /*<<< orphan*/  slave_lch; } ;

/* Variables and functions */
 int /*<<< orphan*/  edma_free_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edma_free_slot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edma_unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct davinci_runtime_data*) ; 

__attribute__((used)) static int davinci_pcm_close(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct davinci_runtime_data *prtd = runtime->private_data;

	edma_unlink(prtd->slave_lch);

	edma_free_slot(prtd->slave_lch);
	edma_free_channel(prtd->master_lch);

	kfree(prtd);

	return 0;
}