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
struct video_card {int /*<<< orphan*/  syt_offset; int /*<<< orphan*/  cip_d; int /*<<< orphan*/  cip_n; int /*<<< orphan*/  pal_or_ntsc; int /*<<< orphan*/  channel; } ;
struct dv1394_init {int n_frames; int /*<<< orphan*/  syt_offset; int /*<<< orphan*/  cip_d; int /*<<< orphan*/  cip_n; int /*<<< orphan*/  format; int /*<<< orphan*/  channel; int /*<<< orphan*/  api_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  DV1394_API_VERSION ; 
 int DV1394_MAX_FRAMES ; 
 int do_dv1394_init (struct video_card*,struct dv1394_init*) ; 

__attribute__((used)) static int do_dv1394_init_default(struct video_card *video)
{
	struct dv1394_init init;

	init.api_version = DV1394_API_VERSION;
	init.n_frames = DV1394_MAX_FRAMES / 4;
	init.channel = video->channel;
	init.format = video->pal_or_ntsc;
	init.cip_n = video->cip_n;
	init.cip_d = video->cip_d;
	init.syt_offset = video->syt_offset;

	return do_dv1394_init(video, &init);
}