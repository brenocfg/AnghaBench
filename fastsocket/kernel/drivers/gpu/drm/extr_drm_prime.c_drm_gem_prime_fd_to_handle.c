#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_gem_object {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct drm_file {TYPE_2__ prime; } ;
struct drm_device {TYPE_1__* driver; } ;
typedef  struct drm_gem_object dma_buf ;
struct TYPE_4__ {struct drm_gem_object* (* gem_prime_import ) (struct drm_device*,struct drm_gem_object*) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct drm_gem_object*) ; 
 int PTR_ERR (struct drm_gem_object*) ; 
 struct drm_gem_object* dma_buf_get (int) ; 
 int /*<<< orphan*/  dma_buf_put (struct drm_gem_object*) ; 
 int drm_gem_handle_create (struct drm_file*,struct drm_gem_object*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_handle_unreference_unlocked (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_gem_object_unreference_unlocked (struct drm_gem_object*) ; 
 int drm_prime_add_buf_handle (TYPE_2__*,struct drm_gem_object*,int /*<<< orphan*/ ) ; 
 int drm_prime_lookup_buf_handle (TYPE_2__*,struct drm_gem_object*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_gem_object* stub1 (struct drm_device*,struct drm_gem_object*) ; 

int drm_gem_prime_fd_to_handle(struct drm_device *dev,
		struct drm_file *file_priv, int prime_fd, uint32_t *handle)
{
	struct dma_buf *dma_buf;
	struct drm_gem_object *obj;
	int ret;

	dma_buf = dma_buf_get(prime_fd);
	if (IS_ERR(dma_buf))
		return PTR_ERR(dma_buf);

	mutex_lock(&file_priv->prime.lock);

	ret = drm_prime_lookup_buf_handle(&file_priv->prime,
			dma_buf, handle);
	if (!ret) {
		ret = 0;
		goto out_put;
	}

	/* never seen this one, need to import */
	obj = dev->driver->gem_prime_import(dev, dma_buf);
	if (IS_ERR(obj)) {
		ret = PTR_ERR(obj);
		goto out_put;
	}

	ret = drm_gem_handle_create(file_priv, obj, handle);
	drm_gem_object_unreference_unlocked(obj);
	if (ret)
		goto out_put;

	ret = drm_prime_add_buf_handle(&file_priv->prime,
			dma_buf, *handle);
	if (ret)
		goto fail;

	mutex_unlock(&file_priv->prime.lock);

	dma_buf_put(dma_buf);

	return 0;

fail:
	/* hmm, if driver attached, we are relying on the free-object path
	 * to detach.. which seems ok..
	 */
	drm_gem_object_handle_unreference_unlocked(obj);
out_put:
	dma_buf_put(dma_buf);
	mutex_unlock(&file_priv->prime.lock);
	return ret;
}