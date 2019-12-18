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

/* Variables and functions */
 double dsfmt_gv_genrand_close1_open2 () ; 

__attribute__((used)) inline static double dsfmt_gv_genrand_open_close(void) {
    return 2.0 - dsfmt_gv_genrand_close1_open2();
}