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
struct vx_pipe {int hw_ptr; int align; int transferred; int period_bytes; int /*<<< orphan*/  prepared; } ;
struct vx_core {int chip_status; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int buffer_size; } ;

/* Variables and functions */
 int DMA_READ_ALIGN ; 
 int /*<<< orphan*/  IRQ_CONNECT_STREAM_NEXT ; 
 int VX_STAT_IS_STALE ; 
 int frames_to_bytes (struct snd_pcm_runtime*,int) ; 
 int snd_pcm_capture_avail (struct snd_pcm_runtime*) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  vx_pcm_read_per_bytes (struct vx_core*,struct snd_pcm_runtime*,struct vx_pipe*) ; 
 int /*<<< orphan*/  vx_pseudo_dma_read (struct vx_core*,struct snd_pcm_runtime*,struct vx_pipe*,int) ; 
 int vx_query_hbuffer_size (struct vx_core*,struct vx_pipe*) ; 
 int /*<<< orphan*/  vx_send_rih_nolock (struct vx_core*,int /*<<< orphan*/ ) ; 
 scalar_t__ vx_wait_for_rx_full (struct vx_core*) ; 

__attribute__((used)) static void vx_pcm_capture_update(struct vx_core *chip, struct snd_pcm_substream *subs,
				  struct vx_pipe *pipe)
{
	int size, space, count;
	struct snd_pcm_runtime *runtime = subs->runtime;

	if (! pipe->prepared || (chip->chip_status & VX_STAT_IS_STALE))
		return;

	size = runtime->buffer_size - snd_pcm_capture_avail(runtime);
	if (! size)
		return;
	size = frames_to_bytes(runtime, size);
	space = vx_query_hbuffer_size(chip, pipe);
	if (space < 0)
		goto _error;
	if (size > space)
		size = space;
	size = (size / 3) * 3; /* align to 3 bytes */
	if (size < DMA_READ_ALIGN)
		goto _error;

	/* keep the last 6 bytes, they will be read after disconnection */
	count = size - DMA_READ_ALIGN;
	/* read bytes until the current pointer reaches to the aligned position
	 * for word-transfer
	 */
	while (count > 0) {
		if ((pipe->hw_ptr % pipe->align) == 0)
			break;
		if (vx_wait_for_rx_full(chip) < 0)
			goto _error;
		vx_pcm_read_per_bytes(chip, runtime, pipe);
		count -= 3;
	}
	if (count > 0) {
		/* ok, let's accelerate! */
		int align = pipe->align * 3;
		space = (count / align) * align;
		vx_pseudo_dma_read(chip, runtime, pipe, space);
		count -= space;
	}
	/* read the rest of bytes */
	while (count > 0) {
		if (vx_wait_for_rx_full(chip) < 0)
			goto _error;
		vx_pcm_read_per_bytes(chip, runtime, pipe);
		count -= 3;
	}
	/* disconnect the host, SIZE_HBUF command always switches to the stream mode */
	vx_send_rih_nolock(chip, IRQ_CONNECT_STREAM_NEXT);
	/* read the last pending 6 bytes */
	count = DMA_READ_ALIGN;
	while (count > 0) {
		vx_pcm_read_per_bytes(chip, runtime, pipe);
		count -= 3;
	}
	/* update the position */
	pipe->transferred += size;
	if (pipe->transferred >= pipe->period_bytes) {
		pipe->transferred %= pipe->period_bytes;
		snd_pcm_period_elapsed(subs);
	}
	return;

 _error:
	/* disconnect the host, SIZE_HBUF command always switches to the stream mode */
	vx_send_rih_nolock(chip, IRQ_CONNECT_STREAM_NEXT);
	return;
}