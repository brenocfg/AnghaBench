#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct TYPE_5__ {struct saa7134_dev* dev; TYPE_3__ timeout; int /*<<< orphan*/  queue; } ;
struct saa7134_dev {int ctl_mute; size_t board; TYPE_1__ video_q; scalar_t__ automute; int /*<<< orphan*/  tda9887_conf; scalar_t__ ctl_automute; scalar_t__ ctl_invert; scalar_t__ ctl_volume; scalar_t__ ctl_saturation; scalar_t__ ctl_hue; scalar_t__ ctl_contrast; scalar_t__ ctl_bright; } ;
struct TYPE_8__ {scalar_t__ default_value; } ;
struct TYPE_6__ {scalar_t__ video_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int PAGE_MASK ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  TDA9887_AUTOMUTE ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_VOLUME ; 
 int /*<<< orphan*/  V4L2_CID_BRIGHTNESS ; 
 int /*<<< orphan*/  V4L2_CID_CONTRAST ; 
 int /*<<< orphan*/  V4L2_CID_HUE ; 
 int /*<<< orphan*/  V4L2_CID_PRIVATE_AUTOMUTE ; 
 int /*<<< orphan*/  V4L2_CID_PRIVATE_INVERT ; 
 int /*<<< orphan*/  V4L2_CID_SATURATION ; 
 int VIDEO_MAX_FRAME ; 
 TYPE_4__* ctrl_by_id (int /*<<< orphan*/ ) ; 
 int gbuffers ; 
 int gbufsize ; 
 int gbufsize_max ; 
 int /*<<< orphan*/  init_timer (TYPE_3__*) ; 
 TYPE_2__* saa7134_boards ; 
 int /*<<< orphan*/  saa7134_buffer_timeout ; 
 int /*<<< orphan*/  saa7134_videoport_init (struct saa7134_dev*) ; 

int saa7134_video_init1(struct saa7134_dev *dev)
{
	/* sanitycheck insmod options */
	if (gbuffers < 2 || gbuffers > VIDEO_MAX_FRAME)
		gbuffers = 2;
	if (gbufsize < 0 || gbufsize > gbufsize_max)
		gbufsize = gbufsize_max;
	gbufsize = (gbufsize + PAGE_SIZE - 1) & PAGE_MASK;

	/* put some sensible defaults into the data structures ... */
	dev->ctl_bright     = ctrl_by_id(V4L2_CID_BRIGHTNESS)->default_value;
	dev->ctl_contrast   = ctrl_by_id(V4L2_CID_CONTRAST)->default_value;
	dev->ctl_hue        = ctrl_by_id(V4L2_CID_HUE)->default_value;
	dev->ctl_saturation = ctrl_by_id(V4L2_CID_SATURATION)->default_value;
	dev->ctl_volume     = ctrl_by_id(V4L2_CID_AUDIO_VOLUME)->default_value;
	dev->ctl_mute       = 1; // ctrl_by_id(V4L2_CID_AUDIO_MUTE)->default_value;
	dev->ctl_invert     = ctrl_by_id(V4L2_CID_PRIVATE_INVERT)->default_value;
	dev->ctl_automute   = ctrl_by_id(V4L2_CID_PRIVATE_AUTOMUTE)->default_value;

	if (dev->tda9887_conf && dev->ctl_automute)
		dev->tda9887_conf |= TDA9887_AUTOMUTE;
	dev->automute       = 0;

	INIT_LIST_HEAD(&dev->video_q.queue);
	init_timer(&dev->video_q.timeout);
	dev->video_q.timeout.function = saa7134_buffer_timeout;
	dev->video_q.timeout.data     = (unsigned long)(&dev->video_q);
	dev->video_q.dev              = dev;

	if (saa7134_boards[dev->board].video_out)
		saa7134_videoport_init(dev);

	return 0;
}