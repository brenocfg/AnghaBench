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
struct drm_i915_private {int crt_ddc_pin; } ;
struct bdb_header {int dummy; } ;
struct bdb_general_definitions {int crt_ddc_gmbus_pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDB_GENERAL_DEFINITIONS ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 struct bdb_general_definitions* find_section (struct bdb_header*,int /*<<< orphan*/ ) ; 
 int get_blocksize (struct bdb_general_definitions*) ; 
 scalar_t__ intel_gmbus_is_port_valid (int) ; 

__attribute__((used)) static void
parse_general_definitions(struct drm_i915_private *dev_priv,
			  struct bdb_header *bdb)
{
	struct bdb_general_definitions *general;

	general = find_section(bdb, BDB_GENERAL_DEFINITIONS);
	if (general) {
		u16 block_size = get_blocksize(general);
		if (block_size >= sizeof(*general)) {
			int bus_pin = general->crt_ddc_gmbus_pin;
			DRM_DEBUG_KMS("crt_ddc_bus_pin: %d\n", bus_pin);
			if (intel_gmbus_is_port_valid(bus_pin))
				dev_priv->crt_ddc_pin = bus_pin;
		} else {
			DRM_DEBUG_KMS("BDB_GD too small (%d). Invalid.\n",
				      block_size);
		}
	}
}