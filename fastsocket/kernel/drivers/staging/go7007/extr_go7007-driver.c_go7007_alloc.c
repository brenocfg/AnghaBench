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
struct go7007_board_info {int sensor_flags; int sensor_width; int sensor_height; int sensor_framerate; int /*<<< orphan*/  sensor_h_offset; int /*<<< orphan*/  sensor_v_offset; } ;
struct go7007 {int tuner_type; int width; int height; int sensor_framerate; int bitrate; int fps_scale; int /*<<< orphan*/  stream; scalar_t__ audio_enabled; int /*<<< orphan*/ * audio_deliver; scalar_t__* modet_map; TYPE_1__* modet; scalar_t__ interlace_coding; scalar_t__ dvd_mode; scalar_t__ gop_header_enable; scalar_t__ seq_header_enable; scalar_t__ repeat_seqhead; scalar_t__ closed_gop; scalar_t__ ipb; scalar_t__ gop_size; int /*<<< orphan*/  aspect_ratio; scalar_t__ pali; int /*<<< orphan*/  format; scalar_t__ streaming; scalar_t__ encoder_subsample; scalar_t__ encoder_v_halve; scalar_t__ encoder_h_halve; int /*<<< orphan*/  encoder_h_offset; int /*<<< orphan*/  encoder_v_offset; int /*<<< orphan*/  standard; scalar_t__ input; scalar_t__ in_use; int /*<<< orphan*/  interrupt_waitq; scalar_t__ interrupt_available; scalar_t__ i2c_adapter_online; int /*<<< orphan*/  i2c_adapter; int /*<<< orphan*/  status; scalar_t__ ref_count; int /*<<< orphan*/ * video_dev; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  frame_waitq; int /*<<< orphan*/  hw_lock; scalar_t__* name; scalar_t__ channel_number; scalar_t__ board_id; struct go7007_board_info* board_info; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GO7007_FORMAT_MJPEG ; 
 int /*<<< orphan*/  GO7007_RATIO_1_1 ; 
 int GO7007_SENSOR_TV ; 
 int /*<<< orphan*/  GO7007_STD_NTSC ; 
 int /*<<< orphan*/  GO7007_STD_OTHER ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_INIT ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct go7007* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct go7007 *go7007_alloc(struct go7007_board_info *board, struct device *dev)
{
	struct go7007 *go;
	int i;

	go = kmalloc(sizeof(struct go7007), GFP_KERNEL);
	if (go == NULL)
		return NULL;
	go->dev = dev;
	go->board_info = board;
	go->board_id = 0;
	go->tuner_type = -1;
	go->channel_number = 0;
	go->name[0] = 0;
	mutex_init(&go->hw_lock);
	init_waitqueue_head(&go->frame_waitq);
	spin_lock_init(&go->spinlock);
	go->video_dev = NULL;
	go->ref_count = 0;
	go->status = STATUS_INIT;
	memset(&go->i2c_adapter, 0, sizeof(go->i2c_adapter));
	go->i2c_adapter_online = 0;
	go->interrupt_available = 0;
	init_waitqueue_head(&go->interrupt_waitq);
	go->in_use = 0;
	go->input = 0;
	if (board->sensor_flags & GO7007_SENSOR_TV) {
		go->standard = GO7007_STD_NTSC;
		go->width = 720;
		go->height = 480;
		go->sensor_framerate = 30000;
	} else {
		go->standard = GO7007_STD_OTHER;
		go->width = board->sensor_width;
		go->height = board->sensor_height;
		go->sensor_framerate = board->sensor_framerate;
	}
	go->encoder_v_offset = board->sensor_v_offset;
	go->encoder_h_offset = board->sensor_h_offset;
	go->encoder_h_halve = 0;
	go->encoder_v_halve = 0;
	go->encoder_subsample = 0;
	go->streaming = 0;
	go->format = GO7007_FORMAT_MJPEG;
	go->bitrate = 1500000;
	go->fps_scale = 1;
	go->pali = 0;
	go->aspect_ratio = GO7007_RATIO_1_1;
	go->gop_size = 0;
	go->ipb = 0;
	go->closed_gop = 0;
	go->repeat_seqhead = 0;
	go->seq_header_enable = 0;
	go->gop_header_enable = 0;
	go->dvd_mode = 0;
	go->interlace_coding = 0;
	for (i = 0; i < 4; ++i)
		go->modet[i].enable = 0;;
	for (i = 0; i < 1624; ++i)
		go->modet_map[i] = 0;
	go->audio_deliver = NULL;
	go->audio_enabled = 0;
	INIT_LIST_HEAD(&go->stream);

	return go;
}