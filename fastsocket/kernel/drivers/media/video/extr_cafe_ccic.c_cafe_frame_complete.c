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
struct cafe_camera {int next_buf; int state; int /*<<< orphan*/  s_tasklet; int /*<<< orphan*/  iowait; int /*<<< orphan*/  nbufs; int /*<<< orphan*/  specframes; scalar_t__ sequence; scalar_t__* buf_seq; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CF_DMA_ACTIVE ; 
 int S_IDLE ; 
#define  S_SINGLEREAD 130 
#define  S_SPECREAD 129 
#define  S_STREAMING 128 
 int /*<<< orphan*/  cafe_ctlr_irq_disable (struct cafe_camera*) ; 
 int /*<<< orphan*/  cafe_ctlr_stop (struct cafe_camera*) ; 
 int /*<<< orphan*/  cam_err (struct cafe_camera*,char*,...) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ printk_ratelimit () ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cafe_frame_complete(struct cafe_camera *cam, int frame)
{
	/*
	 * Basic frame housekeeping.
	 */
	if (test_bit(frame, &cam->flags) && printk_ratelimit())
		cam_err(cam, "Frame overrun on %d, frames lost\n", frame);
	set_bit(frame, &cam->flags);
	clear_bit(CF_DMA_ACTIVE, &cam->flags);
	if (cam->next_buf < 0)
		cam->next_buf = frame;
	cam->buf_seq[frame] = ++(cam->sequence);

	switch (cam->state) {
	/*
	 * If in single read mode, try going speculative.
	 */
	    case S_SINGLEREAD:
		cam->state = S_SPECREAD;
		cam->specframes = 0;
		wake_up(&cam->iowait);
		break;

	/*
	 * If we are already doing speculative reads, and nobody is
	 * reading them, just stop.
	 */
	    case S_SPECREAD:
		if (++(cam->specframes) >= cam->nbufs) {
			cafe_ctlr_stop(cam);
			cafe_ctlr_irq_disable(cam);
			cam->state = S_IDLE;
		}
		wake_up(&cam->iowait);
		break;
	/*
	 * For the streaming case, we defer the real work to the
	 * camera tasklet.
	 *
	 * FIXME: if the application is not consuming the buffers,
	 * we should eventually put things on hold and restart in
	 * vidioc_dqbuf().
	 */
	    case S_STREAMING:
		tasklet_schedule(&cam->s_tasklet);
		break;

	    default:
		cam_err(cam, "Frame interrupt in non-operational state\n");
		break;
	}
}