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
struct hdsp {scalar_t__ io_type; } ;

/* Variables and functions */
 scalar_t__ H9632 ; 
 unsigned int HDSP_SPDIFErrorFlag ; 
#define  HDSP_spdifFrequency128KHz 136 
#define  HDSP_spdifFrequency176_4KHz 135 
#define  HDSP_spdifFrequency192KHz 134 
#define  HDSP_spdifFrequency32KHz 133 
#define  HDSP_spdifFrequency44_1KHz 132 
#define  HDSP_spdifFrequency48KHz 131 
#define  HDSP_spdifFrequency64KHz 130 
#define  HDSP_spdifFrequency88_2KHz 129 
#define  HDSP_spdifFrequency96KHz 128 
 unsigned int HDSP_spdifFrequencyMask ; 
 unsigned int HDSP_spdifFrequencyMask_9632 ; 
 int /*<<< orphan*/  HDSP_statusRegister ; 
 unsigned int hdsp_read (struct hdsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_printk (char*,unsigned int,unsigned int) ; 

__attribute__((used)) static int hdsp_spdif_sample_rate(struct hdsp *hdsp)
{
	unsigned int status = hdsp_read(hdsp, HDSP_statusRegister);
	unsigned int rate_bits = (status & HDSP_spdifFrequencyMask);

	/* For the 9632, the mask is different */
	if (hdsp->io_type == H9632)
		 rate_bits = (status & HDSP_spdifFrequencyMask_9632);

	if (status & HDSP_SPDIFErrorFlag)
		return 0;

	switch (rate_bits) {
	case HDSP_spdifFrequency32KHz: return 32000;
	case HDSP_spdifFrequency44_1KHz: return 44100;
	case HDSP_spdifFrequency48KHz: return 48000;
	case HDSP_spdifFrequency64KHz: return 64000;
	case HDSP_spdifFrequency88_2KHz: return 88200;
	case HDSP_spdifFrequency96KHz: return 96000;
	case HDSP_spdifFrequency128KHz:
		if (hdsp->io_type == H9632) return 128000;
		break;
	case HDSP_spdifFrequency176_4KHz:
		if (hdsp->io_type == H9632) return 176400;
		break;
	case HDSP_spdifFrequency192KHz:
		if (hdsp->io_type == H9632) return 192000;
		break;
	default:
		break;
	}
	snd_printk ("Hammerfall-DSP: unknown spdif frequency status; bits = 0x%x, status = 0x%x\n", rate_bits, status);
	return 0;
}