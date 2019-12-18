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
struct vm_area_struct {int dummy; } ;
struct file {struct cx8800_fh* private_data; } ;
struct cx8800_fh {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_queue (struct cx8800_fh*) ; 
 int videobuf_mmap_mapper (int /*<<< orphan*/ ,struct vm_area_struct*) ; 

__attribute__((used)) static int
video_mmap(struct file *file, struct vm_area_struct * vma)
{
	struct cx8800_fh *fh = file->private_data;

	return videobuf_mmap_mapper(get_queue(fh), vma);
}