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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  dt_stat_token ;
typedef  int /*<<< orphan*/  dt_stat_time_t ;

/* Variables and functions */
 int /*<<< orphan*/  dt_stat_stable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_stat_time_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_stat_time_end_batch (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getppid () ; 

__attribute__((used)) static void loop_getppid(dt_stat_time_t s) {
	do {
		dt_stat_token start = dt_stat_time_begin(s);
		for (uint32_t i = 0; i<100; i++) {
			getppid();
			getppid();
			getppid();
			getppid();
			getppid();
			getppid();
			getppid();
			getppid();
			getppid();
			getppid();
		}
		dt_stat_time_end_batch(s, 1000, start);
	} while (!dt_stat_stable(s));
}