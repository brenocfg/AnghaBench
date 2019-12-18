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
struct pp_cam_entry {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  IEEE1284_MODE_ECP ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  parport_negotiate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ForwardSetup(struct pp_cam_entry *cam)
{
	int retry;

	/* The CPiA uses ECP protocol for Downloads from the Host to the camera.
	 * This will be software-emulated if ECP hardware is not present
	 */

	/* the usual camera maximum response time is 10ms, but after receiving
	 * some commands, it needs up to 40ms. (Data Sheet p. 32)*/

	for(retry = 0; retry < 4; ++retry) {
		if(!parport_negotiate(cam->port, IEEE1284_MODE_ECP)) {
			break;
		}
		mdelay(10);
	}
	if(retry == 4) {
		DBG("Unable to negotiate IEEE1284 ECP Download mode\n");
		return -1;
	}
	return 0;
}