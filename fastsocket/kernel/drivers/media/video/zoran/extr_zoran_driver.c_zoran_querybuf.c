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
struct zoran_fh {struct zoran* zr; } ;
struct zoran {int /*<<< orphan*/  resource_lock; } ;
struct v4l2_buffer {int /*<<< orphan*/  index; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int zoran_v4l2_buffer_status (struct zoran_fh*,struct v4l2_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zoran_querybuf(struct file *file, void *__fh, struct v4l2_buffer *buf)
{
	struct zoran_fh *fh = __fh;
	struct zoran *zr = fh->zr;
	int res;

	mutex_lock(&zr->resource_lock);
	res = zoran_v4l2_buffer_status(fh, buf, buf->index);
	mutex_unlock(&zr->resource_lock);

	return res;
}