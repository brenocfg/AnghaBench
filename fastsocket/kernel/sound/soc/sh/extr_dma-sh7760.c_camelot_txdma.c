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
struct camelot_pcm {int tx_period; int /*<<< orphan*/  tx_ss; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void camelot_txdma(void *data)
{
	struct camelot_pcm *cam = data;
	cam->tx_period ^= 1;
	snd_pcm_period_elapsed(cam->tx_ss);
}