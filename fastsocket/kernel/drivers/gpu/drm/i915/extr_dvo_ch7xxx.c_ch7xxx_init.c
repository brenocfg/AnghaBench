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
typedef  scalar_t__ uint8_t ;
struct intel_dvo_device {scalar_t__ slave_addr; struct ch7xxx_priv* dev_priv; struct i2c_adapter* i2c_bus; } ;
struct i2c_adapter {scalar_t__ name; } ;
struct ch7xxx_priv {int quiet; } ;

/* Variables and functions */
 scalar_t__ CH7xxx_DID ; 
 int /*<<< orphan*/  CH7xxx_REG_DID ; 
 int /*<<< orphan*/  CH7xxx_REG_VID ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* ch7xxx_get_id (scalar_t__) ; 
 int /*<<< orphan*/  ch7xxx_readb (struct intel_dvo_device*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  kfree (struct ch7xxx_priv*) ; 
 struct ch7xxx_priv* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ch7xxx_init(struct intel_dvo_device *dvo,
			struct i2c_adapter *adapter)
{
	/* this will detect the CH7xxx chip on the specified i2c bus */
	struct ch7xxx_priv *ch7xxx;
	uint8_t vendor, device;
	char *name;

	ch7xxx = kzalloc(sizeof(struct ch7xxx_priv), GFP_KERNEL);
	if (ch7xxx == NULL)
		return false;

	dvo->i2c_bus = adapter;
	dvo->dev_priv = ch7xxx;
	ch7xxx->quiet = true;

	if (!ch7xxx_readb(dvo, CH7xxx_REG_VID, &vendor))
		goto out;

	name = ch7xxx_get_id(vendor);
	if (!name) {
		DRM_DEBUG_KMS("ch7xxx not detected; got 0x%02x from %s "
				"slave %d.\n",
			  vendor, adapter->name, dvo->slave_addr);
		goto out;
	}


	if (!ch7xxx_readb(dvo, CH7xxx_REG_DID, &device))
		goto out;

	if (device != CH7xxx_DID) {
		DRM_DEBUG_KMS("ch7xxx not detected; got 0x%02x from %s "
				"slave %d.\n",
			  vendor, adapter->name, dvo->slave_addr);
		goto out;
	}

	ch7xxx->quiet = false;
	DRM_DEBUG_KMS("Detected %s chipset, vendor/device ID 0x%02x/0x%02x\n",
		  name, vendor, device);
	return true;
out:
	kfree(ch7xxx);
	return false;
}