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
struct TYPE_2__ {int block_size; struct idal_buffer* idal_buf; } ;
struct tape_device {TYPE_1__ char_data; } ;
struct idal_buffer {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (int,char*,int,int) ; 
 int /*<<< orphan*/  DBF_LH (int,char*,int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct idal_buffer*) ; 
 int MAX_BLOCKSIZE ; 
 struct idal_buffer* idal_buffer_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idal_buffer_free (struct idal_buffer*) ; 

int
tape_std_mtsetblk(struct tape_device *device, int count)
{
	struct idal_buffer *new;

	DBF_LH(6, "tape_std_mtsetblk(%d)\n", count);
	if (count <= 0) {
		/*
		 * Just set block_size to 0. tapechar_read/tapechar_write
		 * will realloc the idal buffer if a bigger one than the
		 * current is needed.
		 */
		device->char_data.block_size = 0;
		return 0;
	}
	if (device->char_data.idal_buf != NULL &&
	    device->char_data.idal_buf->size == count)
		/* We already have a idal buffer of that size. */
		return 0;

	if (count > MAX_BLOCKSIZE) {
		DBF_EVENT(3, "Invalid block size (%d > %d) given.\n",
			count, MAX_BLOCKSIZE);
		return -EINVAL;
	}

	/* Allocate a new idal buffer. */
	new = idal_buffer_alloc(count, 0);
	if (IS_ERR(new))
		return -ENOMEM;
	if (device->char_data.idal_buf != NULL)
		idal_buffer_free(device->char_data.idal_buf);
	device->char_data.idal_buf = new;
	device->char_data.block_size = count;

	DBF_LH(6, "new blocksize is %d\n", device->char_data.block_size);

	return 0;
}