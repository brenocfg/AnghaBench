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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i1480_CET_VS1 ; 
 int /*<<< orphan*/  i1480_est_fd00 ; 
 int /*<<< orphan*/  i1480_est_fd01 ; 
 int /*<<< orphan*/  uwb_est_unregister (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i1480_est_exit(void)
{
	uwb_est_unregister(i1480_CET_VS1, 0x00, 0x8086, 0x0c3b,
			   i1480_est_fd00, ARRAY_SIZE(i1480_est_fd00));
	uwb_est_unregister(i1480_CET_VS1, 0x01, 0x8086, 0x0c3b,
			   i1480_est_fd01, ARRAY_SIZE(i1480_est_fd01));
}