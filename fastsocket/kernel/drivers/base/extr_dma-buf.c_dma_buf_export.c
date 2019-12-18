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
struct file {int dummy; } ;
struct dma_buf_ops {int /*<<< orphan*/  mmap; int /*<<< orphan*/  kmap; int /*<<< orphan*/  kmap_atomic; int /*<<< orphan*/  release; int /*<<< orphan*/  unmap_dma_buf; int /*<<< orphan*/  map_dma_buf; } ;
struct dma_buf {size_t size; int /*<<< orphan*/  attachments; int /*<<< orphan*/  lock; struct file* file; struct dma_buf_ops const* ops; void* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct dma_buf* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ WARN_ON (int) ; 
 struct file* anon_inode_getfile (char*,int /*<<< orphan*/ *,struct dma_buf*,int) ; 
 int /*<<< orphan*/  dma_buf_fops ; 
 struct dma_buf* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct dma_buf *dma_buf_export(void *priv, const struct dma_buf_ops *ops,
				size_t size, int flags)
{
	struct dma_buf *dmabuf;
	struct file *file;

	if (WARN_ON(!priv || !ops
			  || !ops->map_dma_buf
			  || !ops->unmap_dma_buf
			  || !ops->release
			  || !ops->kmap_atomic
			  || !ops->kmap
			  || !ops->mmap)) {
		return ERR_PTR(-EINVAL);
	}

	dmabuf = kzalloc(sizeof(struct dma_buf), GFP_KERNEL);
	if (dmabuf == NULL)
		return ERR_PTR(-ENOMEM);

	dmabuf->priv = priv;
	dmabuf->ops = ops;
	dmabuf->size = size;

	file = anon_inode_getfile("dmabuf", &dma_buf_fops, dmabuf, flags);

	dmabuf->file = file;

	mutex_init(&dmabuf->lock);
	INIT_LIST_HEAD(&dmabuf->attachments);

	return dmabuf;
}