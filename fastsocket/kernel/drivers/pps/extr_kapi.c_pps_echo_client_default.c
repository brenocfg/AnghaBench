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
struct pps_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PPS_CAPTUREASSERT ; 
 int PPS_CAPTURECLEAR ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char*,char*) ; 

__attribute__((used)) static void pps_echo_client_default(struct pps_device *pps, int event,
		void *data)
{
	dev_info(pps->dev, "echo %s %s\n",
		event & PPS_CAPTUREASSERT ? "assert" : "",
		event & PPS_CAPTURECLEAR ? "clear" : "");
}