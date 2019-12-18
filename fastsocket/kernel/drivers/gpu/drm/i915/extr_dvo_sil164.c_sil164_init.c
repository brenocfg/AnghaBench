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
struct sil164_priv {int quiet; } ;
struct intel_dvo_device {int /*<<< orphan*/  slave_addr; struct sil164_priv* dev_priv; struct i2c_adapter* i2c_bus; } ;
struct i2c_adapter {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SIL164_DID ; 
 int /*<<< orphan*/  SIL164_DID_LO ; 
 int SIL164_VID ; 
 int /*<<< orphan*/  SIL164_VID_LO ; 
 int /*<<< orphan*/  kfree (struct sil164_priv*) ; 
 struct sil164_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sil164_readb (struct intel_dvo_device*,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static bool sil164_init(struct intel_dvo_device *dvo,
			struct i2c_adapter *adapter)
{
	/* this will detect the SIL164 chip on the specified i2c bus */
	struct sil164_priv *sil;
	unsigned char ch;

	sil = kzalloc(sizeof(struct sil164_priv), GFP_KERNEL);
	if (sil == NULL)
		return false;

	dvo->i2c_bus = adapter;
	dvo->dev_priv = sil;
	sil->quiet = true;

	if (!sil164_readb(dvo, SIL164_VID_LO, &ch))
		goto out;

	if (ch != (SIL164_VID & 0xff)) {
		DRM_DEBUG_KMS("sil164 not detected got %d: from %s Slave %d.\n",
			  ch, adapter->name, dvo->slave_addr);
		goto out;
	}

	if (!sil164_readb(dvo, SIL164_DID_LO, &ch))
		goto out;

	if (ch != (SIL164_DID & 0xff)) {
		DRM_DEBUG_KMS("sil164 not detected got %d: from %s Slave %d.\n",
			  ch, adapter->name, dvo->slave_addr);
		goto out;
	}
	sil->quiet = false;

	DRM_DEBUG_KMS("init sil164 dvo controller successfully!\n");
	return true;

out:
	kfree(sil);
	return false;
}