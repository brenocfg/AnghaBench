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
struct snd_pcm_substream {int dummy; } ;
struct snd_dbri {int /*<<< orphan*/  lock; } ;
struct dbri_streaminfo {int pipe; int /*<<< orphan*/  size; scalar_t__ offset; } ;

/* Variables and functions */
 scalar_t__ DBRI_PLAY ; 
 struct dbri_streaminfo* DBRI_STREAM (struct snd_dbri*,struct snd_pcm_substream*) ; 
 scalar_t__ DBRI_STREAMNO (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  D_USR ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int setup_descs (struct snd_dbri*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct snd_dbri* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_dbri_prepare(struct snd_pcm_substream *substream)
{
	struct snd_dbri *dbri = snd_pcm_substream_chip(substream);
	struct dbri_streaminfo *info = DBRI_STREAM(dbri, substream);
	int ret;

	info->size = snd_pcm_lib_buffer_bytes(substream);
	if (DBRI_STREAMNO(substream) == DBRI_PLAY)
		info->pipe = 4;	/* Send pipe */
	else
		info->pipe = 6;	/* Receive pipe */

	spin_lock_irq(&dbri->lock);
	info->offset = 0;

	/* Setup the all the transmit/receive descriptors to cover the
	 * whole DMA buffer.
	 */
	ret = setup_descs(dbri, DBRI_STREAMNO(substream),
			  snd_pcm_lib_period_bytes(substream));

	spin_unlock_irq(&dbri->lock);

	dprintk(D_USR, "prepare audio output. %d bytes\n", info->size);
	return ret;
}