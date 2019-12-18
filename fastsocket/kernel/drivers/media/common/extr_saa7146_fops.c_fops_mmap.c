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
struct videobuf_queue {int dummy; } ;
struct saa7146_fh {int type; struct videobuf_queue vbi_q; struct videobuf_queue video_q; } ;
struct file {struct saa7146_fh* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DEB_EE (char*) ; 
#define  V4L2_BUF_TYPE_VBI_CAPTURE 129 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE 128 
 int videobuf_mmap_mapper (struct videobuf_queue*,struct vm_area_struct*) ; 

__attribute__((used)) static int fops_mmap(struct file *file, struct vm_area_struct * vma)
{
	struct saa7146_fh *fh = file->private_data;
	struct videobuf_queue *q;

	switch (fh->type) {
	case V4L2_BUF_TYPE_VIDEO_CAPTURE: {
		DEB_EE(("V4L2_BUF_TYPE_VIDEO_CAPTURE: file:%p, vma:%p\n",file, vma));
		q = &fh->video_q;
		break;
		}
	case V4L2_BUF_TYPE_VBI_CAPTURE: {
		DEB_EE(("V4L2_BUF_TYPE_VBI_CAPTURE: file:%p, vma:%p\n",file, vma));
		q = &fh->vbi_q;
		break;
		}
	default:
		BUG();
		return 0;
	}

	return videobuf_mmap_mapper(q,vma);
}