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
 int /*<<< orphan*/  w83697hf_set_reg (int,int) ; 

__attribute__((used)) static void w83697hf_write_timeout(int timeout)
{
	/* Write Timeout counter to CRF4 */
	w83697hf_set_reg(0xF4, timeout);
}