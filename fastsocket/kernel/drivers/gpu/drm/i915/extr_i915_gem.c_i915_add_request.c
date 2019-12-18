#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct intel_ring_buffer {int (* add_request ) (struct intel_ring_buffer*) ;scalar_t__ outstanding_lazy_request; int /*<<< orphan*/  request_list; TYPE_1__* dev; } ;
struct drm_i915_gem_request {int /*<<< orphan*/  seqno; int /*<<< orphan*/  client_list; struct drm_i915_file_private* file_priv; int /*<<< orphan*/  list; scalar_t__ emitted_jiffies; int /*<<< orphan*/  tail; struct intel_ring_buffer* ring; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  request_list; } ;
struct drm_i915_file_private {TYPE_2__ mm; } ;
struct drm_file {struct drm_i915_file_private* driver_priv; } ;
struct TYPE_9__ {int /*<<< orphan*/  retire_work; int /*<<< orphan*/  suspended; } ;
struct TYPE_8__ {int /*<<< orphan*/  hangcheck_timer; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; TYPE_4__ mm; int /*<<< orphan*/  wq; TYPE_3__ gpu_error; } ;
typedef  TYPE_5__ drm_i915_private_t ;
struct TYPE_6__ {TYPE_5__* dev_private; } ;

/* Variables and functions */
 scalar_t__ DRM_I915_HANGCHECK_JIFFIES ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HZ ; 
 scalar_t__ i915_enable_hangcheck ; 
 int /*<<< orphan*/  intel_mark_busy (int /*<<< orphan*/ ) ; 
 int intel_ring_flush_all_caches (struct intel_ring_buffer*) ; 
 int /*<<< orphan*/  intel_ring_get_seqno (struct intel_ring_buffer*) ; 
 int /*<<< orphan*/  intel_ring_get_tail (struct intel_ring_buffer*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (struct drm_i915_gem_request*) ; 
 struct drm_i915_gem_request* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies_up (scalar_t__) ; 
 int /*<<< orphan*/  round_jiffies_up_relative (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct intel_ring_buffer*) ; 
 int /*<<< orphan*/  trace_i915_gem_request_add (struct intel_ring_buffer*,int /*<<< orphan*/ ) ; 

int
i915_add_request(struct intel_ring_buffer *ring,
		 struct drm_file *file,
		 u32 *out_seqno)
{
	drm_i915_private_t *dev_priv = ring->dev->dev_private;
	struct drm_i915_gem_request *request;
	u32 request_ring_position;
	int was_empty;
	int ret;

	/*
	 * Emit any outstanding flushes - execbuf can fail to emit the flush
	 * after having emitted the batchbuffer command. Hence we need to fix
	 * things up similar to emitting the lazy request. The difference here
	 * is that the flush _must_ happen before the next request, no matter
	 * what.
	 */
	ret = intel_ring_flush_all_caches(ring);
	if (ret)
		return ret;

	request = kmalloc(sizeof(*request), GFP_KERNEL);
	if (request == NULL)
		return -ENOMEM;


	/* Record the position of the start of the request so that
	 * should we detect the updated seqno part-way through the
	 * GPU processing the request, we never over-estimate the
	 * position of the head.
	 */
	request_ring_position = intel_ring_get_tail(ring);

	ret = ring->add_request(ring);
	if (ret) {
		kfree(request);
		return ret;
	}

	request->seqno = intel_ring_get_seqno(ring);
	request->ring = ring;
	request->tail = request_ring_position;
	request->emitted_jiffies = jiffies;
	was_empty = list_empty(&ring->request_list);
	list_add_tail(&request->list, &ring->request_list);
	request->file_priv = NULL;

	if (file) {
		struct drm_i915_file_private *file_priv = file->driver_priv;

		spin_lock(&file_priv->mm.lock);
		request->file_priv = file_priv;
		list_add_tail(&request->client_list,
			      &file_priv->mm.request_list);
		spin_unlock(&file_priv->mm.lock);
	}

	trace_i915_gem_request_add(ring, request->seqno);
	ring->outstanding_lazy_request = 0;

	if (!dev_priv->mm.suspended) {
		if (i915_enable_hangcheck) {
			mod_timer(&dev_priv->gpu_error.hangcheck_timer,
				  round_jiffies_up(jiffies + DRM_I915_HANGCHECK_JIFFIES));
		}
		if (was_empty) {
			queue_delayed_work(dev_priv->wq,
					   &dev_priv->mm.retire_work,
					   round_jiffies_up_relative(HZ));
			intel_mark_busy(dev_priv->dev);
		}
	}

	if (out_seqno)
		*out_seqno = request->seqno;
	return 0;
}