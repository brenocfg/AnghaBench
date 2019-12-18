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
struct be_adapter {int eeh_error; int hw_error; int fw_timeout; } ;

/* Variables and functions */

__attribute__((used)) static inline void  be_clear_all_error(struct be_adapter *adapter)
{
	adapter->eeh_error = false;
	adapter->hw_error = false;
	adapter->fw_timeout = false;
}