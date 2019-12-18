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
struct file {int f_mode; } ;
struct TYPE_2__ {int play_sample_size; int rec_sample_size; scalar_t__ base; } ;
typedef  scalar_t__ LPDAQD ;

/* Variables and functions */
#define  AFMT_S16_LE 129 
#define  AFMT_U8 128 
 scalar_t__ DAPQ_DATA_BUFF ; 
 scalar_t__ DAQDS__size ; 
 scalar_t__ DAQDS_wSampleSize ; 
 scalar_t__ DARQ_DATA_BUFF ; 
 int DEFSAMPLESIZE ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 TYPE_1__ dev ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int dsp_set_format(struct file *file, int val)
{
	int data, i;
	LPDAQD lpDAQ, lpDARQ;

	lpDAQ = dev.base + DAPQ_DATA_BUFF;
	lpDARQ = dev.base + DARQ_DATA_BUFF;

	switch (val) {
	case AFMT_U8:
	case AFMT_S16_LE:
		data = val;
		break;
	default:
		data = DEFSAMPLESIZE;
		break;
	}

	for (i = 0; i < 3; ++i, lpDAQ += DAQDS__size, lpDARQ += DAQDS__size) {
		if (file->f_mode & FMODE_WRITE)
			writew(data, lpDAQ + DAQDS_wSampleSize);
		if (file->f_mode & FMODE_READ)
			writew(data, lpDARQ + DAQDS_wSampleSize);
	}
	if (file->f_mode & FMODE_WRITE)
		dev.play_sample_size = data;
	if (file->f_mode & FMODE_READ)
		dev.rec_sample_size = data;

	return data;
}