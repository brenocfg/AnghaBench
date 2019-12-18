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
struct tfp410_priv {int quiet; } ;
struct intel_dvo_device {int /*<<< orphan*/  slave_addr; struct tfp410_priv* dev_priv; struct i2c_adapter* i2c_bus; } ;
struct i2c_adapter {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TFP410_DID ; 
 int /*<<< orphan*/  TFP410_DID_LO ; 
 int TFP410_VID ; 
 int /*<<< orphan*/  TFP410_VID_LO ; 
 int /*<<< orphan*/  kfree (struct tfp410_priv*) ; 
 struct tfp410_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int tfp410_getid (struct intel_dvo_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool tfp410_init(struct intel_dvo_device *dvo,
			struct i2c_adapter *adapter)
{
	/* this will detect the tfp410 chip on the specified i2c bus */
	struct tfp410_priv *tfp;
	int id;

	tfp = kzalloc(sizeof(struct tfp410_priv), GFP_KERNEL);
	if (tfp == NULL)
		return false;

	dvo->i2c_bus = adapter;
	dvo->dev_priv = tfp;
	tfp->quiet = true;

	if ((id = tfp410_getid(dvo, TFP410_VID_LO)) != TFP410_VID) {
		DRM_DEBUG_KMS("tfp410 not detected got VID %X: from %s "
				"Slave %d.\n",
			  id, adapter->name, dvo->slave_addr);
		goto out;
	}

	if ((id = tfp410_getid(dvo, TFP410_DID_LO)) != TFP410_DID) {
		DRM_DEBUG_KMS("tfp410 not detected got DID %X: from %s "
				"Slave %d.\n",
			  id, adapter->name, dvo->slave_addr);
		goto out;
	}
	tfp->quiet = false;
	return true;
out:
	kfree(tfp);
	return false;
}