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
struct hw_data {int dummy; } ;
typedef  int /*<<< orphan*/  ChanInfo ;

/* Variables and functions */
 int /*<<< orphan*/  hal_set_current_channel_ex (struct hw_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hal_set_current_channel(struct hw_data *pHwData, ChanInfo channel)
{
	hal_set_current_channel_ex(pHwData, channel);
}