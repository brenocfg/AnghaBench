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
struct drm_buf {scalar_t__ total; TYPE_1__* dev_private; } ;
struct TYPE_2__ {scalar_t__ currently_mapped; int /*<<< orphan*/ * virtual; } ;
typedef  TYPE_1__ drm_i810_buf_priv_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ I810_BUF_MAPPED ; 
 scalar_t__ I810_BUF_UNMAPPED ; 
 int vm_munmap (unsigned long,size_t) ; 

__attribute__((used)) static int i810_unmap_buffer(struct drm_buf *buf)
{
	drm_i810_buf_priv_t *buf_priv = buf->dev_private;
	int retcode = 0;

	if (buf_priv->currently_mapped != I810_BUF_MAPPED)
		return -EINVAL;

	retcode = vm_munmap((unsigned long)buf_priv->virtual,
			    (size_t) buf->total);

	buf_priv->currently_mapped = I810_BUF_UNMAPPED;
	buf_priv->virtual = NULL;

	return retcode;
}