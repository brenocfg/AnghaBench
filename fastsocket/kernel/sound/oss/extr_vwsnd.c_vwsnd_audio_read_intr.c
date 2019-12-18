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
 unsigned int LI_INTR_COMM1_OVERFLOW ; 
 unsigned int READ_INTR_MASK ; 
 int /*<<< orphan*/  pcm_input (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vwsnd_audio_read_intr(vwsnd_dev_t *devc, unsigned int status)
{
	int overflown = status & LI_INTR_COMM1_OVERFLOW;

	if (status & READ_INTR_MASK)
		pcm_input(devc, overflown, 0);
}