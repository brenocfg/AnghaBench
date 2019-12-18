#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intel_connector {TYPE_1__* edid; } ;
struct i2c_adapter {int dummy; } ;
struct edid {int dummy; } ;
struct drm_connector {int dummy; } ;
struct TYPE_3__ {int extensions; } ;

/* Variables and functions */
 int EDID_LENGTH ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 struct edid* drm_get_edid (struct drm_connector*,struct i2c_adapter*) ; 
 struct edid* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct edid*,TYPE_1__*,int) ; 
 struct intel_connector* to_intel_connector (struct drm_connector*) ; 

__attribute__((used)) static struct edid *
intel_dp_get_edid(struct drm_connector *connector, struct i2c_adapter *adapter)
{
	struct intel_connector *intel_connector = to_intel_connector(connector);

	/* use cached edid if we have one */
	if (intel_connector->edid) {
		struct edid *edid;
		int size;

		/* invalid edid */
		if (IS_ERR(intel_connector->edid))
			return NULL;

		size = (intel_connector->edid->extensions + 1) * EDID_LENGTH;
		edid = kmalloc(size, GFP_KERNEL);
		if (!edid)
			return NULL;

		memcpy(edid, intel_connector->edid, size);
		return edid;
	}

	return drm_get_edid(connector, adapter);
}