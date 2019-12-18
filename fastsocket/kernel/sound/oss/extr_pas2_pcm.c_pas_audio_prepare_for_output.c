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

/* Variables and functions */
 int /*<<< orphan*/  pas_audio_reset (int) ; 

__attribute__((used)) static int pas_audio_prepare_for_output(int dev, int bsize, int bcount)
{
	pas_audio_reset(dev);
	return 0;
}