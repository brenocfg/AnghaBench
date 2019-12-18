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
struct carlu {int stop_event_polling; int /*<<< orphan*/  event_thread; int /*<<< orphan*/  event_pipe; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct carlu* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct carlu*) ; 
 scalar_t__ IS_ERR_OR_NULL (struct carlu*) ; 
 int PTR_ERR (struct carlu*) ; 
 int /*<<< orphan*/  SDL_CreateThread (int /*<<< orphan*/ ,struct carlu*) ; 
 int carlu_cmd_echo (struct carlu*,int) ; 
 int /*<<< orphan*/  carlu_fw_info (struct carlu*) ; 
 int /*<<< orphan*/  carlusb_destroy (struct carlu*) ; 
 int /*<<< orphan*/  carlusb_event_thread ; 
 int /*<<< orphan*/  carlusb_free_driver (struct carlu*) ; 
 int carlusb_initialize_rxirq (struct carlu*) ; 
 int carlusb_initialize_rxrings (struct carlu*) ; 
 int carlusb_load_firmware (struct carlu*) ; 
 struct carlu* carlusb_open () ; 
 int carlusb_show_devinfo (struct carlu*) ; 
 int carlusb_upload_firmware (struct carlu*,int) ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int /*<<< orphan*/  info (char*) ; 
 int pipe (int /*<<< orphan*/ ) ; 

struct carlu *carlusb_probe(void)
{
	struct carlu *ar;
	int ret = -ENOMEM;

	ar = carlusb_open();
	if (IS_ERR_OR_NULL(ar)) {
		if (IS_ERR(ar))
			ret = PTR_ERR(ar);
		goto err_out;
	}

	ret = carlusb_show_devinfo(ar);
	if (ret)
		goto err_out;

	ret = carlusb_load_firmware(ar);
	if (ret)
		goto err_out;

	ret = pipe(ar->event_pipe);
	if (ret)
		goto err_out;

	ar->stop_event_polling = false;
	ar->event_thread = SDL_CreateThread(carlusb_event_thread, ar);

	ret = carlusb_upload_firmware(ar, true);
	if (ret)
		goto err_kill;

	ret = carlusb_initialize_rxirq(ar);
	if (ret)
		goto err_kill;

	ret = carlusb_initialize_rxrings(ar);
	if (ret)
		goto err_kill;

	ret = carlu_cmd_echo(ar, 0x44110dee);
	if (ret) {
		err("echo test failed...\n");
		goto err_kill;
	}

	info("firmware is active and running.\n");

	carlu_fw_info(ar);

	return ar;

err_kill:
	carlusb_destroy(ar);

err_out:
	carlusb_free_driver(ar);
	err("usb device rendezvous failed (%d).\n", ret);
	return ERR_PTR(ret);
}