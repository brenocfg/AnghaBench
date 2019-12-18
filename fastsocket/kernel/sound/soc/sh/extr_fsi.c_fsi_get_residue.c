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
struct snd_pcm_runtime {int dummy; } ;
struct fsi_priv {int chan; int /*<<< orphan*/  dma_chan; TYPE_1__* substream; } ;
struct TYPE_2__ {struct snd_pcm_runtime* runtime; } ;

/* Variables and functions */
 int frames_to_bytes (struct snd_pcm_runtime*,int) ; 
 int fsi_get_fifo_residue (struct fsi_priv*,int) ; 
 int get_dma_residue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsi_get_residue(struct fsi_priv *fsi, int is_play)
{
	int residue;
	int width;
	struct snd_pcm_runtime *runtime;

	runtime = fsi->substream->runtime;

	/* get 1 channel data width */
	width = frames_to_bytes(runtime, 1) / fsi->chan;

	if (2 == width)
		residue = fsi_get_fifo_residue(fsi, is_play);
	else
		residue = get_dma_residue(fsi->dma_chan);

	return residue;
}