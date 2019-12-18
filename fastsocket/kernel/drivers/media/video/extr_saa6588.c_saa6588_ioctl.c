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
struct v4l2_subdev {int dummy; } ;
struct saa6588_command {int result; int /*<<< orphan*/  event_list; int /*<<< orphan*/  instance; } ;
struct saa6588 {int data_available_for_read; int /*<<< orphan*/  read_queue; } ;

/* Variables and functions */
 long ENOIOCTLCMD ; 
 int POLLIN ; 
 int POLLRDNORM ; 
#define  SAA6588_CMD_CLOSE 131 
#define  SAA6588_CMD_OPEN 130 
#define  SAA6588_CMD_POLL 129 
#define  SAA6588_CMD_READ 128 
 int /*<<< orphan*/  poll_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_from_buf (struct saa6588*,struct saa6588_command*) ; 
 struct saa6588* to_saa6588 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long saa6588_ioctl(struct v4l2_subdev *sd, unsigned int cmd, void *arg)
{
	struct saa6588 *s = to_saa6588(sd);
	struct saa6588_command *a = arg;

	switch (cmd) {
		/* --- open() for /dev/radio --- */
	case SAA6588_CMD_OPEN:
		a->result = 0;	/* return error if chip doesn't work ??? */
		break;
		/* --- close() for /dev/radio --- */
	case SAA6588_CMD_CLOSE:
		s->data_available_for_read = 1;
		wake_up_interruptible(&s->read_queue);
		a->result = 0;
		break;
		/* --- read() for /dev/radio --- */
	case SAA6588_CMD_READ:
		read_from_buf(s, a);
		break;
		/* --- poll() for /dev/radio --- */
	case SAA6588_CMD_POLL:
		a->result = 0;
		if (s->data_available_for_read) {
			a->result |= POLLIN | POLLRDNORM;
		}
		poll_wait(a->instance, &s->read_queue, a->event_list);
		break;

	default:
		/* nothing */
		return -ENOIOCTLCMD;
	}
	return 0;
}