#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned char NumberOfSamples; unsigned char* SampleNumber; } ;
struct TYPE_6__ {TYPE_1__ ms; } ;
struct TYPE_7__ {int number; TYPE_2__ hdr; } ;
typedef  TYPE_3__ wavefront_patch_info ;
typedef  int /*<<< orphan*/  snd_wavefront_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ,char*,int,unsigned char) ; 
 int EIO ; 
 int /*<<< orphan*/  WFC_UPLOAD_MULTISAMPLE ; 
 int /*<<< orphan*/  WF_DEBUG_DATA ; 
 unsigned char demunge_int32 (unsigned char*,int) ; 
 int /*<<< orphan*/  munge_int32 (int,unsigned char*,int) ; 
 int /*<<< orphan*/  snd_printk (char*) ; 
 scalar_t__ snd_wavefront_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,unsigned char*) ; 
 int wavefront_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
wavefront_fetch_multisample (snd_wavefront_t *dev, 
			     wavefront_patch_info *header)
{
	int i;
	unsigned char log_ns[1];
	unsigned char number[2];
	int num_samples;

	munge_int32 (header->number, number, 2);
    
	if (snd_wavefront_cmd (dev, WFC_UPLOAD_MULTISAMPLE, log_ns, number)) {
		snd_printk ("upload multisample failed.\n");
		return -(EIO);
	}
    
	DPRINT (WF_DEBUG_DATA, "msample %d has %d samples\n",
				header->number, log_ns[0]);

	header->hdr.ms.NumberOfSamples = log_ns[0];

	/* get the number of samples ... */

	num_samples = (1 << log_ns[0]);
    
	for (i = 0; i < num_samples; i++) {
		char d[2];
		int val;
	
		if ((val = wavefront_read (dev)) == -1) {
			snd_printk ("upload multisample failed "
				    "during sample loop.\n");
			return -(EIO);
		}
		d[0] = val;

		if ((val = wavefront_read (dev)) == -1) {
			snd_printk ("upload multisample failed "
				    "during sample loop.\n");
			return -(EIO);
		}
		d[1] = val;
	
		header->hdr.ms.SampleNumber[i] =
			demunge_int32 ((unsigned char *) d, 2);
	
		DPRINT (WF_DEBUG_DATA, "msample sample[%d] = %d\n",
					i, header->hdr.ms.SampleNumber[i]);
	}

	return (0);
}