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
typedef  int /*<<< orphan*/  vwsnd_dev_t ;

/* Variables and functions */
 unsigned int LI_INTR_COMM2_UNDERFLOW ; 
 unsigned int WRITE_INTR_MASK ; 
 int /*<<< orphan*/  pcm_output (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vwsnd_audio_write_intr(vwsnd_dev_t *devc, unsigned int status)
{
	int underflown = status & LI_INTR_COMM2_UNDERFLOW;

	if (status & WRITE_INTR_MASK)
		pcm_output(devc, underflown, 0);
}