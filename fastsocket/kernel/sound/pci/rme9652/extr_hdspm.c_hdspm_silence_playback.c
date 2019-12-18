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
struct hdspm {int period_bytes; void* playback_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDSPM_CHANNEL_BUFFER_BYTES ; 
 int HDSPM_MAX_CHANNELS ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hdspm_silence_playback(struct hdspm *hdspm)
{
	int i;
	int n = hdspm->period_bytes;
	void *buf = hdspm->playback_buffer;

	if (buf == NULL)
		return;

	for (i = 0; i < HDSPM_MAX_CHANNELS; i++) {
		memset(buf, 0, n);
		buf += HDSPM_CHANNEL_BUFFER_BYTES;
	}
}