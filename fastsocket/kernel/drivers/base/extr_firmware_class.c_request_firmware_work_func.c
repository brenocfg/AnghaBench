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
struct firmware_work {int /*<<< orphan*/  module; int /*<<< orphan*/  context; int /*<<< orphan*/  (* cont ) (struct firmware const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  uevent; int /*<<< orphan*/  device; int /*<<< orphan*/  name; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int _request_firmware (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct firmware_work*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct firmware const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
request_firmware_work_func(void *arg)
{
	struct firmware_work *fw_work = arg;
	const struct firmware *fw;
	int ret;
	if (!arg) {
		WARN_ON(1);
		return 0;
	}
	ret = _request_firmware(&fw, fw_work->name, fw_work->device,
		fw_work->uevent);

	fw_work->cont(fw, fw_work->context);

	module_put(fw_work->module);
	kfree(fw_work);
	return ret;
}