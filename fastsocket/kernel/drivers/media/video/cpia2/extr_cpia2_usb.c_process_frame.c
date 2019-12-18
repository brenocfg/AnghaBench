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
struct camera_data {int first_image_seen; int num_frames; TYPE_1__* workbuff; TYPE_1__* curbuff; scalar_t__ mmapped; } ;
struct TYPE_2__ {unsigned char* data; int length; int max_length; void* status; int /*<<< orphan*/  num; struct TYPE_2__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 void* FRAME_EMPTY ; 
 void* FRAME_ERROR ; 
 void* FRAME_READY ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void process_frame(struct camera_data *cam)
{
	static int frame_count;

	unsigned char *inbuff = cam->workbuff->data;

	DBG("Processing frame #%d, current:%d\n",
	    cam->workbuff->num, cam->curbuff->num);

	if(cam->workbuff->length > cam->workbuff->max_length)
		cam->workbuff->max_length = cam->workbuff->length;

	if ((inbuff[0] == 0xFF) && (inbuff[1] == 0xD8)) {
		frame_count++;
	} else {
		cam->workbuff->status = FRAME_ERROR;
		DBG("Start of frame not found\n");
		return;
	}

	/***
	 * Now the output buffer should have a JPEG image in it.
	 ***/
	if(!cam->first_image_seen) {
		/* Always skip the first image after streaming
		 * starts. It is almost certainly corrupt. */
		cam->first_image_seen = 1;
		cam->workbuff->status = FRAME_EMPTY;
		return;
	}
	if (cam->workbuff->length > 3) {
		if(cam->mmapped &&
		   cam->workbuff->length < cam->workbuff->max_length) {
			/* No junk in the buffers */
			memset(cam->workbuff->data+cam->workbuff->length,
			       0, cam->workbuff->max_length-
				  cam->workbuff->length);
		}
		cam->workbuff->max_length = cam->workbuff->length;
		cam->workbuff->status = FRAME_READY;

		if(!cam->mmapped && cam->num_frames > 2) {
			/* During normal reading, the most recent
			 * frame will be read.  If the current frame
			 * hasn't started reading yet, it will never
			 * be read, so mark it empty.  If the buffer is
			 * mmapped, or we have few buffers, we need to
			 * wait for the user to free the buffer.
			 *
			 * NOTE: This is not entirely foolproof with 3
			 * buffers, but it would take an EXTREMELY
			 * overloaded system to cause problems (possible
			 * image data corruption).  Basically, it would
			 * need to take more time to execute cpia2_read
			 * than it would for the camera to send
			 * cam->num_frames-2 frames before problems
			 * could occur.
			 */
			cam->curbuff->status = FRAME_EMPTY;
		}
		cam->curbuff = cam->workbuff;
		cam->workbuff = cam->workbuff->next;
		DBG("Changed buffers, work:%d, current:%d\n",
		    cam->workbuff->num, cam->curbuff->num);
		return;
	} else {
		DBG("Not enough data for an image.\n");
	}

	cam->workbuff->status = FRAME_ERROR;
	return;
}