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
typedef  int u32 ;
struct b3dfg_dev {int frame_size; int /*<<< orphan*/  triplets_dropped_lock; int /*<<< orphan*/  cstate_lock; int /*<<< orphan*/  buffer_lock; int /*<<< orphan*/  buffer_waitqueue; int /*<<< orphan*/  buffer_queue; struct b3dfg_buffer* buffers; } ;
struct b3dfg_buffer {int /*<<< orphan*/  list; int /*<<< orphan*/ * frame; } ;

/* Variables and functions */
 int B3DFG_FRAMES_PER_BUFFER ; 
 int /*<<< orphan*/  B3D_REG_FRM_SIZE ; 
 int /*<<< orphan*/  B3D_REG_HW_CTRL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int b3dfg_nbuf ; 
 int b3dfg_read32 (struct b3dfg_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b3dfg_write32 (struct b3dfg_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_all_frame_buffers (struct b3dfg_dev*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 struct b3dfg_buffer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int b3dfg_init_dev(struct b3dfg_dev *fgdev)
{
	int i, j;
	u32 frm_size = b3dfg_read32(fgdev, B3D_REG_FRM_SIZE);

	/* Disable interrupts. In abnormal circumstances (e.g. after a crash)
	 * the board may still be transmitting from the previous session. If we
	 * ensure that interrupts are disabled before we later enable them, we
	 * are sure to capture a triplet from the start, rather than starting
	 * from frame 2 or 3. Disabling interrupts causes the FG to throw away
	 * all buffered data and stop buffering more until interrupts are
	 * enabled again.
	 */
	b3dfg_write32(fgdev, B3D_REG_HW_CTRL, 0);

	fgdev->frame_size = frm_size * 4096;
	fgdev->buffers = kzalloc(sizeof(struct b3dfg_buffer) * b3dfg_nbuf,
				 GFP_KERNEL);
	if (!fgdev->buffers)
		goto err_no_buf;
	for (i = 0; i < b3dfg_nbuf; i++) {
		struct b3dfg_buffer *buf = &fgdev->buffers[i];
		for (j = 0; j < B3DFG_FRAMES_PER_BUFFER; j++) {
			buf->frame[j] = kmalloc(fgdev->frame_size, GFP_KERNEL);
			if (!buf->frame[j])
				goto err_no_mem;
		}
		INIT_LIST_HEAD(&buf->list);
	}

	INIT_LIST_HEAD(&fgdev->buffer_queue);
	init_waitqueue_head(&fgdev->buffer_waitqueue);
	spin_lock_init(&fgdev->buffer_lock);
	spin_lock_init(&fgdev->cstate_lock);
	spin_lock_init(&fgdev->triplets_dropped_lock);
	return 0;

err_no_mem:
	free_all_frame_buffers(fgdev);
err_no_buf:
	return -ENOMEM;
}