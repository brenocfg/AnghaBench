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
 int /*<<< orphan*/  DMAbuf_start_devices (unsigned int) ; 
#define  LOCL_STARTAUDIO 128 

__attribute__((used)) static void seq_local_event(unsigned char *event_rec)
{
	unsigned char   cmd = event_rec[1];
	unsigned int    parm = *((unsigned int *) &event_rec[4]);

	switch (cmd)
	{
		case LOCL_STARTAUDIO:
			DMAbuf_start_devices(parm);
			break;

		default:;
	}
}