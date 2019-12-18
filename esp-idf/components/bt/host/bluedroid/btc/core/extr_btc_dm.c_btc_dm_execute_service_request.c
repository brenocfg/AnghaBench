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
typedef  int /*<<< orphan*/  tBTA_SERVICE_ID ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  btc_in_execute_service_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void btc_dm_execute_service_request(BOOLEAN enable, char *p_param)
{
    btc_in_execute_service_request(*((tBTA_SERVICE_ID *)p_param), enable);
}