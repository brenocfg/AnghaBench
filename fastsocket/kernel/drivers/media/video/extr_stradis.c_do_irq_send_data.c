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
struct saa7146 {scalar_t__ playmode; int audtail; int audhead; int vidhead; int vidtail; scalar_t__ osdtail; scalar_t__ osdhead; int /*<<< orphan*/  vidq; scalar_t__ vidbuf; scalar_t__ dmadebi; int /*<<< orphan*/  audq; scalar_t__ audbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBM_MP2_AUD_FIFO ; 
 int /*<<< orphan*/  IBM_MP2_AUD_FIFOW ; 
 int /*<<< orphan*/  IBM_MP2_FIFO ; 
 int /*<<< orphan*/  IBM_MP2_FIFOW ; 
 scalar_t__ NewCard ; 
 int /*<<< orphan*/  SAA7146_IER ; 
 int SAA7146_PSR_DEBI_S ; 
 int SAA7146_PSR_PIN1 ; 
 scalar_t__ VID_PLAY_NORMAL ; 
 int /*<<< orphan*/  debAudio ; 
 int /*<<< orphan*/  debNormal ; 
 int /*<<< orphan*/  debVideo ; 
 int debiread (struct saa7146*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debiwrite (struct saa7146*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  saawrite (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_irq_send_data(struct saa7146 *saa)
{
	int split, audbytes, vidbytes;

	saawrite(SAA7146_PSR_PIN1, SAA7146_IER);
	/* if special feature mode in effect, disable audio sending */
	if (saa->playmode != VID_PLAY_NORMAL)
		saa->audtail = saa->audhead = 0;
	if (saa->audhead <= saa->audtail)
		audbytes = saa->audtail - saa->audhead;
	else
		audbytes = 65536 - (saa->audhead - saa->audtail);
	if (saa->vidhead <= saa->vidtail)
		vidbytes = saa->vidtail - saa->vidhead;
	else
		vidbytes = 524288 - (saa->vidhead - saa->vidtail);
	if (audbytes == 0 && vidbytes == 0 && saa->osdtail == saa->osdhead) {
		saawrite(0, SAA7146_IER);
		return;
	}
	/* if at least 1 block audio waiting and audio fifo isn't full */
	if (audbytes >= 2048 && (debiread(saa, debNormal, IBM_MP2_AUD_FIFO, 2)
			& 0xff) < 60) {
		if (saa->audhead > saa->audtail)
			split = 65536 - saa->audhead;
		else
			split = 0;
		audbytes = 2048;
		if (split > 0 && split < 2048) {
			memcpy(saa->dmadebi, saa->audbuf + saa->audhead, split);
			saa->audhead = 0;
			audbytes -= split;
		} else
			split = 0;
		memcpy(saa->dmadebi + split, saa->audbuf + saa->audhead,
			audbytes);
		saa->audhead += audbytes;
		saa->audhead &= 0xffff;
		debiwrite(saa, debAudio, (NewCard ? IBM_MP2_AUD_FIFO :
			IBM_MP2_AUD_FIFOW), 0, 2048);
		wake_up_interruptible(&saa->audq);
		/* if at least 1 block video waiting and video fifo isn't full */
	} else if (vidbytes >= 30720 && (debiread(saa, debNormal,
						  IBM_MP2_FIFO, 2)) < 16384) {
		if (saa->vidhead > saa->vidtail)
			split = 524288 - saa->vidhead;
		else
			split = 0;
		vidbytes = 30720;
		if (split > 0 && split < 30720) {
			memcpy(saa->dmadebi, saa->vidbuf + saa->vidhead, split);
			saa->vidhead = 0;
			vidbytes -= split;
		} else
			split = 0;
		memcpy(saa->dmadebi + split, saa->vidbuf + saa->vidhead,
			vidbytes);
		saa->vidhead += vidbytes;
		saa->vidhead &= 0x7ffff;
		debiwrite(saa, debVideo, (NewCard ? IBM_MP2_FIFO :
					  IBM_MP2_FIFOW), 0, 30720);
		wake_up_interruptible(&saa->vidq);
	}
	saawrite(SAA7146_PSR_DEBI_S | SAA7146_PSR_PIN1, SAA7146_IER);
}