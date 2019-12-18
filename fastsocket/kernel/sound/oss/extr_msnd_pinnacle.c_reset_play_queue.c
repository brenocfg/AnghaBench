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
struct TYPE_2__ {int last_playbank; int play_sample_size; int play_channels; int play_sample_rate; scalar_t__ base; scalar_t__ DAPQ; } ;
typedef  scalar_t__ LPDAQD ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ DAPQ_DATA_BUFF ; 
 int DAP_BUFF_SIZE ; 
 int DAQDS__size ; 
 scalar_t__ DAQDS_wChannels ; 
 scalar_t__ DAQDS_wFlags ; 
 scalar_t__ DAQDS_wFormat ; 
 scalar_t__ DAQDS_wIntMsg ; 
 scalar_t__ DAQDS_wSampleRate ; 
 scalar_t__ DAQDS_wSampleSize ; 
 scalar_t__ DAQDS_wSize ; 
 scalar_t__ DAQDS_wStart ; 
 int HIMT_PLAY_DONE ; 
 scalar_t__ JQS_wHead ; 
 scalar_t__ JQS_wTail ; 
 int PCTODSP_BASED (int /*<<< orphan*/ ) ; 
 int PCTODSP_OFFSET (int) ; 
 TYPE_1__ dev ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void reset_play_queue(void)
{
	int n;
	LPDAQD lpDAQ;

	dev.last_playbank = -1;
	writew(PCTODSP_OFFSET(0 * DAQDS__size), dev.DAPQ + JQS_wHead);
	writew(PCTODSP_OFFSET(0 * DAQDS__size), dev.DAPQ + JQS_wTail);

	for (n = 0, lpDAQ = dev.base + DAPQ_DATA_BUFF; n < 3; ++n, lpDAQ += DAQDS__size) {
		writew(PCTODSP_BASED((DWORD)(DAP_BUFF_SIZE * n)), lpDAQ + DAQDS_wStart);
		writew(0, lpDAQ + DAQDS_wSize);
		writew(1, lpDAQ + DAQDS_wFormat);
		writew(dev.play_sample_size, lpDAQ + DAQDS_wSampleSize);
		writew(dev.play_channels, lpDAQ + DAQDS_wChannels);
		writew(dev.play_sample_rate, lpDAQ + DAQDS_wSampleRate);
		writew(HIMT_PLAY_DONE * 0x100 + n, lpDAQ + DAQDS_wIntMsg);
		writew(n, lpDAQ + DAQDS_wFlags);
	}
}