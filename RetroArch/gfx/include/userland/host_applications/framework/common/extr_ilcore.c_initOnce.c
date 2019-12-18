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
typedef  scalar_t__ VCOS_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  vcos_demand (int) ; 
 scalar_t__ vcos_mutex_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void initOnce(void)
{
   VCOS_STATUS_T status;
   status = vcos_mutex_create(&lock, VCOS_FUNCTION);
   vcos_demand(status == VCOS_SUCCESS);
}