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
 int pas_read (int) ; 
 int /*<<< orphan*/  pas_write (int,int) ; 
 int pcm_channels ; 
 int /*<<< orphan*/  pcm_set_speed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_speed ; 

__attribute__((used)) static int pcm_set_channels(int arg)
{

	if ((arg != 1) && (arg != 2))
		return pcm_channels;

	if (arg != pcm_channels)
	{
		pas_write(pas_read(0xF8A) ^ 0x20, 0xF8A);

		pcm_channels = arg;
		pcm_set_speed(pcm_speed);	/* The speed must be reinitialized */
	}
	return pcm_channels;
}