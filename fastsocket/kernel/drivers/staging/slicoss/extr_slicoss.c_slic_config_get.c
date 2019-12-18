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
typedef  scalar_t__ u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  SLIC_UPR_RCONFIG ; 
 int slic_upr_request (struct adapter*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void slic_config_get(struct adapter *adapter, u32 config,
							u32 config_h)
{
	int status;

	status = slic_upr_request(adapter,
				  SLIC_UPR_RCONFIG,
				  (u32) config, (u32) config_h, 0, 0);
	ASSERT(status == 0);
}