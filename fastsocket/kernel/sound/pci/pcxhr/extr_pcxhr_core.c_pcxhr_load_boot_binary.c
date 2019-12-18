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
struct TYPE_2__ {unsigned int addr; } ;
struct pcxhr_mgr {TYPE_1__ hostport; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int PCXHR_INPL (struct pcxhr_mgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCXHR_IT_DOWNLOAD_BOOT ; 
 unsigned int PCXHR_MBOX0_HF5 ; 
 int /*<<< orphan*/  PCXHR_OUTPL (struct pcxhr_mgr*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  PCXHR_PLX_MBOX0 ; 
 int /*<<< orphan*/  PCXHR_PLX_MBOX1 ; 
 int /*<<< orphan*/  PCXHR_TIMEOUT_DSP ; 
 int pcxhr_check_reg_bit (struct pcxhr_mgr*,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned char*) ; 
 int pcxhr_download_dsp (struct pcxhr_mgr*,struct firmware const*) ; 
 int pcxhr_send_it_dsp (struct pcxhr_mgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_BUG_ON (unsigned int) ; 

int pcxhr_load_boot_binary(struct pcxhr_mgr *mgr, const struct firmware *boot)
{
	int err;
	unsigned int physaddr = mgr->hostport.addr;
	unsigned char dummy;

	/* send the hostport address to the DSP (only the upper 24 bit !) */
	if (snd_BUG_ON(physaddr & 0xff))
		return -EINVAL;
	PCXHR_OUTPL(mgr, PCXHR_PLX_MBOX1, (physaddr >> 8));

	err = pcxhr_send_it_dsp(mgr, PCXHR_IT_DOWNLOAD_BOOT, 0);
	if (err)
		return err;
	/* clear hf5 bit */
	PCXHR_OUTPL(mgr, PCXHR_PLX_MBOX0,
		    PCXHR_INPL(mgr, PCXHR_PLX_MBOX0) & ~PCXHR_MBOX0_HF5);

	err = pcxhr_download_dsp(mgr, boot);
	if (err)
		return err;
	/* wait for hf5 bit */
	return pcxhr_check_reg_bit(mgr, PCXHR_PLX_MBOX0, PCXHR_MBOX0_HF5,
				   PCXHR_MBOX0_HF5, PCXHR_TIMEOUT_DSP, &dummy);
}