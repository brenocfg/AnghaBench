#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct nic {int flags; scalar_t__ mac; struct firmware const* fw; int /*<<< orphan*/  netdev; TYPE_1__* pdev; } ;
typedef  struct firmware {int size; int* data; } const firmware ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 struct firmware const* ERR_PTR (int) ; 
 char* FIRMWARE_D101M ; 
 char* FIRMWARE_D101S ; 
 char* FIRMWARE_D102E ; 
 int UCODE_SIZE ; 
 int ich ; 
 scalar_t__ mac_82551_10 ; 
 scalar_t__ mac_82551_F ; 
 scalar_t__ mac_82559_D101M ; 
 scalar_t__ mac_82559_D101S ; 
 int /*<<< orphan*/  netif_err (struct nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,int,...) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const struct firmware *e100_request_firmware(struct nic *nic)
{
	const char *fw_name;
	const struct firmware *fw = nic->fw;
	u8 timer, bundle, min_size;
	int err = 0;

	/* do not load u-code for ICH devices */
	if (nic->flags & ich)
		return NULL;

	/* Search for ucode match against h/w revision */
	if (nic->mac == mac_82559_D101M)
		fw_name = FIRMWARE_D101M;
	else if (nic->mac == mac_82559_D101S)
		fw_name = FIRMWARE_D101S;
	else if (nic->mac == mac_82551_F || nic->mac == mac_82551_10)
		fw_name = FIRMWARE_D102E;
	else /* No ucode on other devices */
		return NULL;

	/* If the firmware has not previously been loaded, request a pointer
	 * to it. If it was previously loaded, we are reinitializing the
	 * adapter, possibly in a resume from hibernate, in which case
	 * request_firmware() cannot be used.
	 */
	if (!fw)
		err = request_firmware(&fw, fw_name, &nic->pdev->dev);

	if (err) {
		netif_err(nic, probe, nic->netdev,
			  "Failed to load firmware \"%s\": %d\n",
			  fw_name, err);
		return ERR_PTR(err);
	}

	/* Firmware should be precisely UCODE_SIZE (words) plus three bytes
	   indicating the offsets for BUNDLESMALL, BUNDLEMAX, INTDELAY */
	if (fw->size != UCODE_SIZE * 4 + 3) {
		netif_err(nic, probe, nic->netdev,
			  "Firmware \"%s\" has wrong size %zu\n",
			  fw_name, fw->size);
		release_firmware(fw);
		return ERR_PTR(-EINVAL);
	}

	/* Read timer, bundle and min_size from end of firmware blob */
	timer = fw->data[UCODE_SIZE * 4];
	bundle = fw->data[UCODE_SIZE * 4 + 1];
	min_size = fw->data[UCODE_SIZE * 4 + 2];

	if (timer >= UCODE_SIZE || bundle >= UCODE_SIZE ||
	    min_size >= UCODE_SIZE) {
		netif_err(nic, probe, nic->netdev,
			  "\"%s\" has bogus offset values (0x%x,0x%x,0x%x)\n",
			  fw_name, timer, bundle, min_size);
		release_firmware(fw);
		return ERR_PTR(-EINVAL);
	}

	/* OK, firmware is validated and ready to use. Save a pointer
	 * to it in the nic */
	nic->fw = fw;
	return fw;
}