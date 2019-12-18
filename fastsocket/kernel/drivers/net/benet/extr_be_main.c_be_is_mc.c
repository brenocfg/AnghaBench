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
struct be_adapter {int function_mode; } ;

/* Variables and functions */
 int FLEX10_MODE ; 
 int UMC_ENABLED ; 
 int VNIC_MODE ; 

__attribute__((used)) static inline bool be_is_mc(struct be_adapter *adapter) {
	return (adapter->function_mode & FLEX10_MODE ||
		adapter->function_mode & VNIC_MODE ||
		adapter->function_mode & UMC_ENABLED);
}