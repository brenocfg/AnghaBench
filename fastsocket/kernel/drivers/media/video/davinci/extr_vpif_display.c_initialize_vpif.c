#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct channel_obj {int dummy; } ;
struct TYPE_4__ {scalar_t__ min_numbuffers; scalar_t__* min_bufsize; int* numbuffers; scalar_t__* channel_bufsize; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t VPIF_CHANNEL2_VIDEO ; 
 size_t VPIF_CHANNEL3_VIDEO ; 
 int VPIF_DISPLAY_MAX_DEVICES ; 
 int VPIF_DISPLAY_NUM_CHANNELS ; 
 scalar_t__ ch2_bufsize ; 
 scalar_t__ ch2_numbuffers ; 
 scalar_t__ ch3_bufsize ; 
 scalar_t__ ch3_numbuffers ; 
 TYPE_2__ config_params ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ vpif_obj ; 

__attribute__((used)) static int initialize_vpif(void)
{
	int free_channel_objects_index;
	int free_buffer_channel_index;
	int free_buffer_index;
	int err = 0, i, j;

	/* Default number of buffers should be 3 */
	if ((ch2_numbuffers > 0) &&
	    (ch2_numbuffers < config_params.min_numbuffers))
		ch2_numbuffers = config_params.min_numbuffers;
	if ((ch3_numbuffers > 0) &&
	    (ch3_numbuffers < config_params.min_numbuffers))
		ch3_numbuffers = config_params.min_numbuffers;

	/* Set buffer size to min buffers size if invalid buffer size is
	 * given */
	if (ch2_bufsize < config_params.min_bufsize[VPIF_CHANNEL2_VIDEO])
		ch2_bufsize =
		    config_params.min_bufsize[VPIF_CHANNEL2_VIDEO];
	if (ch3_bufsize < config_params.min_bufsize[VPIF_CHANNEL3_VIDEO])
		ch3_bufsize =
		    config_params.min_bufsize[VPIF_CHANNEL3_VIDEO];

	config_params.numbuffers[VPIF_CHANNEL2_VIDEO] = ch2_numbuffers;

	if (ch2_numbuffers) {
		config_params.channel_bufsize[VPIF_CHANNEL2_VIDEO] =
							ch2_bufsize;
	}
	config_params.numbuffers[VPIF_CHANNEL3_VIDEO] = ch3_numbuffers;

	if (ch3_numbuffers) {
		config_params.channel_bufsize[VPIF_CHANNEL3_VIDEO] =
							ch3_bufsize;
	}

	/* Allocate memory for six channel objects */
	for (i = 0; i < VPIF_DISPLAY_MAX_DEVICES; i++) {
		vpif_obj.dev[i] =
		    kmalloc(sizeof(struct channel_obj), GFP_KERNEL);
		/* If memory allocation fails, return error */
		if (!vpif_obj.dev[i]) {
			free_channel_objects_index = i;
			err = -ENOMEM;
			goto vpif_init_free_channel_objects;
		}
	}

	free_channel_objects_index = VPIF_DISPLAY_MAX_DEVICES;
	free_buffer_channel_index = VPIF_DISPLAY_NUM_CHANNELS;
	free_buffer_index = config_params.numbuffers[i - 1];

	return 0;

vpif_init_free_channel_objects:
	for (j = 0; j < free_channel_objects_index; j++)
		kfree(vpif_obj.dev[j]);
	return err;
}