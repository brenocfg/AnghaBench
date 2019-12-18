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
typedef  int /*<<< orphan*/  v ;
typedef  char u32 ;
struct prpmc2800_board_info {char mem_size; scalar_t__ model; char variant; char core_speed; scalar_t__ bridge_type; char user_flash; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOARD_MODEL ; 
 int BOARD_MODEL_MAX ; 
 scalar_t__ BOARD_MODEL_PRPMC280 ; 
 scalar_t__ BRIDGE_TYPE_MV64362 ; 
 int /*<<< orphan*/  bridge_base ; 
 int /*<<< orphan*/  fatal (char*) ; 
 void* find_node_by_compatible (int /*<<< orphan*/ *,char*) ; 
 void* find_node_by_prop_value_str (int /*<<< orphan*/ *,char*,char*) ; 
 void* finddevice (char*) ; 
 int getprop (void*,char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 char mv64x60_get_mem_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prpmc2800_bridge_setup (char) ; 
 struct prpmc2800_board_info* prpmc2800_get_bip () ; 
 int /*<<< orphan*/  setprop (void*,char*,char*,int) ; 
 char strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void prpmc2800_fixups(void)
{
	u32 v[2], l, mem_size;
	int rc;
	void *devp;
	char model[BOARD_MODEL_MAX];
	struct prpmc2800_board_info *bip;

	bip = prpmc2800_get_bip(); /* Get board info based on VPD */

	mem_size = (bip) ? bip->mem_size : mv64x60_get_mem_size(bridge_base);
	prpmc2800_bridge_setup(mem_size); /* Do necessary bridge setup */

	/* If the VPD doesn't match what we know about, just use the
	 * defaults already in the device tree.
	 */
	if (!bip)
		return;

	/* Know the board type so override device tree defaults */
	/* Set /model appropriately */
	devp = finddevice("/");
	if (devp == NULL)
		fatal("Error: Missing '/' device tree node\n\r");
	memset(model, 0, BOARD_MODEL_MAX);
	strncpy(model, BOARD_MODEL, BOARD_MODEL_MAX - 2);
	l = strlen(model);
	if (bip->model == BOARD_MODEL_PRPMC280)
		l--;
	model[l++] = bip->variant;
	model[l++] = '\0';
	setprop(devp, "model", model, l);

	/* Set /cpus/PowerPC,7447/clock-frequency */
	devp = find_node_by_prop_value_str(NULL, "device_type", "cpu");
	if (devp == NULL)
		fatal("Error: Missing proper cpu device tree node\n\r");
	v[0] = bip->core_speed;
	setprop(devp, "clock-frequency", &v[0], sizeof(v[0]));

	/* Set /memory/reg size */
	devp = finddevice("/memory");
	if (devp == NULL)
		fatal("Error: Missing /memory device tree node\n\r");
	v[0] = 0;
	v[1] = bip->mem_size;
	setprop(devp, "reg", v, sizeof(v));

	/* Update model, if this is a mv64362 */
	if (bip->bridge_type == BRIDGE_TYPE_MV64362) {
		devp = find_node_by_compatible(NULL, "marvell,mv64360");
		if (devp == NULL)
			fatal("Error: Missing marvell,mv64360"
					" device tree node\n\r");
		setprop(devp, "model", "mv64362", strlen("mv64362") + 1);
	}

	/* Set User FLASH size */
	devp = find_node_by_compatible(NULL, "direct-mapped");
	if (devp == NULL)
		fatal("Error: Missing User FLASH device tree node\n\r");
	rc = getprop(devp, "reg", v, sizeof(v));
	if (rc != sizeof(v))
		fatal("Error: Can't find User FLASH reg property\n\r");
	v[1] = bip->user_flash;
	setprop(devp, "reg", v, sizeof(v));
}