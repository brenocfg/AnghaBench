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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_PORTSC ; 
 int /*<<< orphan*/  PORTSC_PTC ; 
 int ffs_nr (int /*<<< orphan*/ ) ; 
 int hw_cread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 hw_port_test_get(void)
{
	return hw_cread(CAP_PORTSC, PORTSC_PTC) >> ffs_nr(PORTSC_PTC);
}