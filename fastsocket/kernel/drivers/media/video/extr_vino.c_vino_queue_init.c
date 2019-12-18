#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vino_framebuffer_queue {scalar_t__ magic; scalar_t__ type; unsigned int length; int /*<<< orphan*/  queue_mutex; int /*<<< orphan*/  out; int /*<<< orphan*/  in; TYPE_1__** buffer; } ;
struct vino_framebuffer {int dummy; } ;
struct TYPE_4__ {unsigned int id; scalar_t__ size; scalar_t__ offset; int /*<<< orphan*/  state_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int VINO_FRAMEBUFFER_COUNT_MAX ; 
 int /*<<< orphan*/  VINO_FRAMEBUFFER_SIZE ; 
 scalar_t__ VINO_MEMORY_MMAP ; 
 scalar_t__ VINO_MEMORY_NONE ; 
 scalar_t__ VINO_QUEUE_MAGIC ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int vino_allocate_buffer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vino_fifo_init (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  vino_queue_free_with_count (struct vino_framebuffer_queue*,unsigned int) ; 

__attribute__((used)) static int vino_queue_init(struct vino_framebuffer_queue *q,
			   unsigned int *length)
{
	unsigned int i;
	int ret = 0;

	dprintk("vino_queue_init(): length = %d\n", *length);

	if (q->magic == VINO_QUEUE_MAGIC) {
		dprintk("vino_queue_init(): queue already initialized!\n");
		return -EINVAL;
	}

	if (q->type != VINO_MEMORY_NONE) {
		dprintk("vino_queue_init(): queue already initialized!\n");
		return -EINVAL;
	}

	if (*length < 1)
		return -EINVAL;

	mutex_lock(&q->queue_mutex);

	if (*length > VINO_FRAMEBUFFER_COUNT_MAX)
		*length = VINO_FRAMEBUFFER_COUNT_MAX;

	q->length = 0;

	for (i = 0; i < *length; i++) {
		dprintk("vino_queue_init(): allocating buffer %d\n", i);
		q->buffer[i] = kmalloc(sizeof(struct vino_framebuffer),
				       GFP_KERNEL);
		if (!q->buffer[i]) {
			dprintk("vino_queue_init(): kmalloc() failed\n");
			ret = -ENOMEM;
			break;
		}

		ret = vino_allocate_buffer(q->buffer[i],
					   VINO_FRAMEBUFFER_SIZE);
		if (ret) {
			kfree(q->buffer[i]);
			dprintk("vino_queue_init(): "
				"vino_allocate_buffer() failed\n");
			break;
		}

		q->buffer[i]->id = i;
		if (i > 0) {
			q->buffer[i]->offset = q->buffer[i - 1]->offset +
				q->buffer[i - 1]->size;
		} else {
			q->buffer[i]->offset = 0;
		}

		spin_lock_init(&q->buffer[i]->state_lock);

		dprintk("vino_queue_init(): buffer = %d, offset = %d, "
			"size = %d\n", i, q->buffer[i]->offset,
			q->buffer[i]->size);
	}

	if (ret) {
		vino_queue_free_with_count(q, i);
		*length = 0;
	} else {
		q->length = *length;
		vino_fifo_init(&q->in, q->length);
		vino_fifo_init(&q->out, q->length);
		q->type = VINO_MEMORY_MMAP;
		q->magic = VINO_QUEUE_MAGIC;
	}

	mutex_unlock(&q->queue_mutex);

	return ret;
}