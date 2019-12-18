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
struct saa7146_vv {struct saa7146_fh* vbi_streaming; } ;
struct saa7146_fh {int dummy; } ;
struct saa7146_dev {struct saa7146_vv* vv_data; } ;
struct file {struct saa7146_fh* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_VBI (char*) ; 
 int /*<<< orphan*/  RESOURCE_DMA3_BRS ; 
 int /*<<< orphan*/  saa7146_res_free (struct saa7146_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbi_stop (struct saa7146_fh*,struct file*) ; 

__attribute__((used)) static void vbi_close(struct saa7146_dev *dev, struct file *file)
{
	struct saa7146_fh *fh = file->private_data;
	struct saa7146_vv *vv = dev->vv_data;
	DEB_VBI(("dev:%p, fh:%p\n",dev,fh));

	if( fh == vv->vbi_streaming ) {
		vbi_stop(fh, file);
	}
	saa7146_res_free(fh, RESOURCE_DMA3_BRS);
}