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
struct carlu {int /*<<< orphan*/  fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170_FIRMWARE_FILE ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  carlfw_load (int /*<<< orphan*/ ) ; 
 int carlu_fw_check (struct carlu*) ; 
 int carlusb_fw_check (struct carlu*) ; 
 int /*<<< orphan*/  dbg (char*) ; 

__attribute__((used)) static int carlusb_load_firmware(struct carlu *ar)
{
	int ret = 0;

	dbg("loading firmware...\n");

	ar->fw = carlfw_load(CARL9170_FIRMWARE_FILE);
	if (IS_ERR_OR_NULL(ar->fw))
		return PTR_ERR(ar->fw);

	ret = carlu_fw_check(ar);
	if (ret)
		return ret;

	ret = carlusb_fw_check(ar);
	if (ret)
		return ret;

	return 0;
}