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
struct go7007_file {scalar_t__ buf_count; scalar_t__ ref_count; struct go7007_file* bufs; scalar_t__ in_use; struct go7007_file* go; } ;
struct go7007 {scalar_t__ buf_count; scalar_t__ ref_count; struct go7007* bufs; scalar_t__ in_use; struct go7007* go; } ;
struct file {struct go7007_file* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  go7007_streamoff (struct go7007_file*) ; 
 int /*<<< orphan*/  kfree (struct go7007_file*) ; 

__attribute__((used)) static int go7007_release(struct file *file)
{
	struct go7007_file *gofh = file->private_data;
	struct go7007 *go = gofh->go;

	if (gofh->buf_count > 0) {
		go7007_streamoff(go);
		go->in_use = 0;
		kfree(gofh->bufs);
		gofh->buf_count = 0;
	}
	kfree(gofh);
	if (--go->ref_count == 0)
		kfree(go);
	file->private_data = NULL;
	return 0;
}