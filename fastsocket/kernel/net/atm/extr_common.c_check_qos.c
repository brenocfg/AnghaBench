#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ traffic_class; } ;
struct atm_qos {TYPE_1__ rxtp; TYPE_1__ txtp; } ;

/* Variables and functions */
 scalar_t__ ATM_ANYCLASS ; 
 int EINVAL ; 
 int check_tp (TYPE_1__*) ; 

__attribute__((used)) static int check_qos(const struct atm_qos *qos)
{
	int error;

	if (!qos->txtp.traffic_class && !qos->rxtp.traffic_class)
		return -EINVAL;
	if (qos->txtp.traffic_class != qos->rxtp.traffic_class &&
	    qos->txtp.traffic_class && qos->rxtp.traffic_class &&
	    qos->txtp.traffic_class != ATM_ANYCLASS &&
	    qos->rxtp.traffic_class != ATM_ANYCLASS) return -EINVAL;
	error = check_tp(&qos->txtp);
	if (error) return error;
	return check_tp(&qos->rxtp);
}