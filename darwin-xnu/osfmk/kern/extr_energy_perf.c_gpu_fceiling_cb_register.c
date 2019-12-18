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
typedef  int /*<<< orphan*/ * gpu_set_fceiling_t ;

/* Variables and functions */
 int /*<<< orphan*/ * gpu_set_fceiling_cb ; 
 int /*<<< orphan*/ * gpu_set_fceiling_cb_default ; 

void gpu_fceiling_cb_register(gpu_set_fceiling_t gnewcb) {
	if (gnewcb != NULL) {
		gpu_set_fceiling_cb = gnewcb;
	} else {
		gpu_set_fceiling_cb = gpu_set_fceiling_cb_default;
	}
}