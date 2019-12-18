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
typedef  int u16 ;
struct drm_i915_private {int child_dev_num; struct child_device_config* child_dev; } ;
struct child_device_config {int /*<<< orphan*/  device_type; } ;
struct bdb_header {int dummy; } ;
struct bdb_general_definitions {int child_dev_size; struct child_device_config* devices; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDB_GENERAL_DEFINITIONS ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct bdb_general_definitions* find_section (struct bdb_header*,int /*<<< orphan*/ ) ; 
 int get_blocksize (struct bdb_general_definitions*) ; 
 struct child_device_config* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

__attribute__((used)) static void
parse_device_mapping(struct drm_i915_private *dev_priv,
		       struct bdb_header *bdb)
{
	struct bdb_general_definitions *p_defs;
	struct child_device_config *p_child, *child_dev_ptr;
	int i, child_device_num, count;
	u16	block_size;

	p_defs = find_section(bdb, BDB_GENERAL_DEFINITIONS);
	if (!p_defs) {
		DRM_DEBUG_KMS("No general definition block is found, no devices defined.\n");
		return;
	}
	/* judge whether the size of child device meets the requirements.
	 * If the child device size obtained from general definition block
	 * is different with sizeof(struct child_device_config), skip the
	 * parsing of sdvo device info
	 */
	if (p_defs->child_dev_size != sizeof(*p_child)) {
		/* different child dev size . Ignore it */
		DRM_DEBUG_KMS("different child size is found. Invalid.\n");
		return;
	}
	/* get the block size of general definitions */
	block_size = get_blocksize(p_defs);
	/* get the number of child device */
	child_device_num = (block_size - sizeof(*p_defs)) /
				sizeof(*p_child);
	count = 0;
	/* get the number of child device that is present */
	for (i = 0; i < child_device_num; i++) {
		p_child = &(p_defs->devices[i]);
		if (!p_child->device_type) {
			/* skip the device block if device type is invalid */
			continue;
		}
		count++;
	}
	if (!count) {
		DRM_DEBUG_KMS("no child dev is parsed from VBT\n");
		return;
	}
	dev_priv->child_dev = kcalloc(count, sizeof(*p_child), GFP_KERNEL);
	if (!dev_priv->child_dev) {
		DRM_DEBUG_KMS("No memory space for child device\n");
		return;
	}

	dev_priv->child_dev_num = count;
	count = 0;
	for (i = 0; i < child_device_num; i++) {
		p_child = &(p_defs->devices[i]);
		if (!p_child->device_type) {
			/* skip the device block if device type is invalid */
			continue;
		}
		child_dev_ptr = dev_priv->child_dev + count;
		count++;
		memcpy((void *)child_dev_ptr, (void *)p_child,
					sizeof(*p_child));
	}
	return;
}