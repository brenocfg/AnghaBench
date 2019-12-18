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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct pcb_config {int config_num; } ;
struct cx231xx {scalar_t__ mode; int /*<<< orphan*/  current_pcb_config; } ;

/* Variables and functions */
 scalar_t__ CX231XX_ANALOG_MODE ; 
 scalar_t__ ENABLE_EP1 ; 
 scalar_t__ ENABLE_EP2 ; 
 scalar_t__ ENABLE_EP3 ; 
 scalar_t__ ENABLE_EP4 ; 
 scalar_t__ ENABLE_EP5 ; 
 scalar_t__ ENABLE_EP6 ; 
 int cx231xx_initialize_stream_xfer (struct cx231xx*,int) ; 
 int cx231xx_start_stream (struct cx231xx*,scalar_t__) ; 
 int cx231xx_stop_stream (struct cx231xx*,scalar_t__) ; 

int cx231xx_capture_start(struct cx231xx *dev, int start, u8 media_type)
{
	int rc = -1;
	u32 ep_mask = -1;
	struct pcb_config *pcb_config;

	/* get EP for media type */
	pcb_config = (struct pcb_config *)&dev->current_pcb_config;

	if (pcb_config->config_num == 1) {
		switch (media_type) {
		case 0:	/* Video */
			ep_mask = ENABLE_EP4;	/* ep4  [00:1000] */
			break;
		case 1:	/* Audio */
			ep_mask = ENABLE_EP3;	/* ep3  [00:0100] */
			break;
		case 2:	/* Vbi */
			ep_mask = ENABLE_EP5;	/* ep5 [01:0000] */
			break;
		case 3:	/* Sliced_cc */
			ep_mask = ENABLE_EP6;	/* ep6 [10:0000] */
			break;
		case 4:	/* ts1 */
		case 6:	/* ts1 parallel mode */
			ep_mask = ENABLE_EP1;	/* ep1 [00:0001] */
			break;
		case 5:	/* ts2 */
			ep_mask = ENABLE_EP2;	/* ep2 [00:0010] */
			break;
		}

	} else if (pcb_config->config_num > 1) {
		switch (media_type) {
		case 0:	/* Video */
			ep_mask = ENABLE_EP4;	/* ep4  [00:1000] */
			break;
		case 1:	/* Audio */
			ep_mask = ENABLE_EP3;	/* ep3  [00:0100] */
			break;
		case 2:	/* Vbi */
			ep_mask = ENABLE_EP5;	/* ep5 [01:0000] */
			break;
		case 3:	/* Sliced_cc */
			ep_mask = ENABLE_EP6;	/* ep6 [10:0000] */
			break;
		case 4:	/* ts1 */
		case 6:	/* ts1 parallel mode */
			ep_mask = ENABLE_EP1;	/* ep1 [00:0001] */
			break;
		case 5:	/* ts2 */
			ep_mask = ENABLE_EP2;	/* ep2 [00:0010] */
			break;
		}

	}

	if (start) {
		rc = cx231xx_initialize_stream_xfer(dev, media_type);

		if (rc < 0)
			return rc;

		/* enable video capture */
		if (ep_mask > 0)
			rc = cx231xx_start_stream(dev, ep_mask);
	} else {
		/* disable video capture */
		if (ep_mask > 0)
			rc = cx231xx_stop_stream(dev, ep_mask);
	}

	if (dev->mode == CX231XX_ANALOG_MODE)
		;/* do any in Analog mode */
	else
		;/* do any in digital mode */

	return rc;
}