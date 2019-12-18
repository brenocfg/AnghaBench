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
struct carlu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  carlu_cmd_reboot (struct carlu*) ; 
 int /*<<< orphan*/  carlusb_destroy (struct carlu*) ; 
 int /*<<< orphan*/  carlusb_free_driver (struct carlu*) ; 

void carlusb_close(struct carlu *ar)
{
	carlu_cmd_reboot(ar);

	carlusb_destroy(ar);
	carlusb_free_driver(ar);
}