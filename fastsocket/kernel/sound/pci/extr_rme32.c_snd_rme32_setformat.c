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
struct rme32 {scalar_t__ iobase; int /*<<< orphan*/  wcreg; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ RME32_IO_CONTROL_REGISTER ; 
 int /*<<< orphan*/  RME32_WCR_MODE24 ; 
#define  SNDRV_PCM_FORMAT_S16_LE 129 
#define  SNDRV_PCM_FORMAT_S32_LE 128 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int snd_rme32_setformat(struct rme32 * rme32, int format)
{
	switch (format) {
	case SNDRV_PCM_FORMAT_S16_LE:
		rme32->wcreg &= ~RME32_WCR_MODE24;
		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		rme32->wcreg |= RME32_WCR_MODE24;
		break;
	default:
		return -EINVAL;
	}
	writel(rme32->wcreg, rme32->iobase + RME32_IO_CONTROL_REGISTER);
	return 0;
}