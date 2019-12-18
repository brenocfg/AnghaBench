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
struct go7007_file {scalar_t__ buf_count; int /*<<< orphan*/  lock; struct go7007* go; } ;
struct go7007 {scalar_t__ status; int /*<<< orphan*/  ref_count; } ;
struct file {struct go7007_file* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ STATUS_ONLINE ; 
 struct go7007_file* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 
 struct go7007* video_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int go7007_open(struct file *file)
{
	struct go7007 *go = video_get_drvdata(video_devdata(file));
	struct go7007_file *gofh;

	if (go->status != STATUS_ONLINE)
		return -EBUSY;
	gofh = kmalloc(sizeof(struct go7007_file), GFP_KERNEL);
	if (gofh == NULL)
		return -ENOMEM;
	++go->ref_count;
	gofh->go = go;
	mutex_init(&gofh->lock);
	gofh->buf_count = 0;
	file->private_data = gofh;
	return 0;
}