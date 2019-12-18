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
struct vx_pipe {int dummy; } ;
struct vx_core {int /*<<< orphan*/  lock; } ;
struct snd_pcm_runtime {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IRQ_CONNECT_STREAM_NEXT ; 
 int /*<<< orphan*/  snd_printd (char*,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int vx_notify_end_of_buffer (struct vx_core*,struct vx_pipe*) ; 
 int /*<<< orphan*/  vx_pseudo_dma_write (struct vx_core*,struct snd_pcm_runtime*,struct vx_pipe*,int) ; 
 int vx_query_hbuffer_size (struct vx_core*,struct vx_pipe*) ; 
 int /*<<< orphan*/  vx_send_rih (struct vx_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vx_send_rih_nolock (struct vx_core*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vx_pcm_playback_transfer_chunk(struct vx_core *chip,
					  struct snd_pcm_runtime *runtime,
					  struct vx_pipe *pipe, int size)
{
	int space, err = 0;

	space = vx_query_hbuffer_size(chip, pipe);
	if (space < 0) {
		/* disconnect the host, SIZE_HBUF command always switches to the stream mode */
		vx_send_rih(chip, IRQ_CONNECT_STREAM_NEXT);
		snd_printd("error hbuffer\n");
		return space;
	}
	if (space < size) {
		vx_send_rih(chip, IRQ_CONNECT_STREAM_NEXT);
		snd_printd("no enough hbuffer space %d\n", space);
		return -EIO; /* XRUN */
	}
		
	/* we don't need irqsave here, because this function
	 * is called from either trigger callback or irq handler
	 */
	spin_lock(&chip->lock); 
	vx_pseudo_dma_write(chip, runtime, pipe, size);
	err = vx_notify_end_of_buffer(chip, pipe);
	/* disconnect the host, SIZE_HBUF command always switches to the stream mode */
	vx_send_rih_nolock(chip, IRQ_CONNECT_STREAM_NEXT);
	spin_unlock(&chip->lock);
	return err;
}