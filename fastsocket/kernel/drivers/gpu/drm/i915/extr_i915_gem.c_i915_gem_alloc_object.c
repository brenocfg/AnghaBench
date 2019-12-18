#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* read_domains; void* write_domain; int /*<<< orphan*/  filp; } ;
struct drm_i915_gem_object {int /*<<< orphan*/  cache_level; TYPE_2__ base; } ;
struct drm_device {int dummy; } ;
struct address_space {int dummy; } ;
typedef  int gfp_t ;
struct TYPE_3__ {struct address_space* i_mapping; } ;

/* Variables and functions */
 int GFP_HIGHUSER ; 
 scalar_t__ HAS_LLC (struct drm_device*) ; 
 int /*<<< orphan*/  I915_CACHE_LLC ; 
 int /*<<< orphan*/  I915_CACHE_NONE ; 
 void* I915_GEM_DOMAIN_CPU ; 
 scalar_t__ IS_BROADWATER (struct drm_device*) ; 
 scalar_t__ IS_CRESTLINE (struct drm_device*) ; 
 int __GFP_DMA32 ; 
 int __GFP_HIGHMEM ; 
 int __GFP_RECLAIMABLE ; 
 scalar_t__ drm_gem_object_init (struct drm_device*,TYPE_2__*,size_t) ; 
 TYPE_1__* file_inode (int /*<<< orphan*/ ) ; 
 struct drm_i915_gem_object* i915_gem_object_alloc (struct drm_device*) ; 
 int /*<<< orphan*/  i915_gem_object_free (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_init (struct drm_i915_gem_object*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_ops ; 
 int /*<<< orphan*/  mapping_set_gfp_mask (struct address_space*,int) ; 

struct drm_i915_gem_object *i915_gem_alloc_object(struct drm_device *dev,
						  size_t size)
{
	struct drm_i915_gem_object *obj;
	struct address_space *mapping;
	gfp_t mask;

	obj = i915_gem_object_alloc(dev);
	if (obj == NULL)
		return NULL;

	if (drm_gem_object_init(dev, &obj->base, size) != 0) {
		i915_gem_object_free(obj);
		return NULL;
	}

	mask = GFP_HIGHUSER | __GFP_RECLAIMABLE;
	if (IS_CRESTLINE(dev) || IS_BROADWATER(dev)) {
		/* 965gm cannot relocate objects above 4GiB. */
		mask &= ~__GFP_HIGHMEM;
		mask |= __GFP_DMA32;
	}

	mapping = file_inode(obj->base.filp)->i_mapping;
	mapping_set_gfp_mask(mapping, mask);

	i915_gem_object_init(obj, &i915_gem_object_ops);

	obj->base.write_domain = I915_GEM_DOMAIN_CPU;
	obj->base.read_domains = I915_GEM_DOMAIN_CPU;

	if (HAS_LLC(dev)) {
		/* On some devices, we can have the GPU use the LLC (the CPU
		 * cache) for about a 10% performance improvement
		 * compared to uncached.  Graphics requests other than
		 * display scanout are coherent with the CPU in
		 * accessing this cache.  This means in this mode we
		 * don't need to clflush on the CPU side, and on the
		 * GPU side we only need to flush internal caches to
		 * get data visible to the CPU.
		 *
		 * However, we maintain the display planes as UC, and so
		 * need to rebind when first used as such.
		 */
		obj->cache_level = I915_CACHE_LLC;
	} else
		obj->cache_level = I915_CACHE_NONE;

	return obj;
}