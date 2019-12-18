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
struct ibmvscsi_host_data {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int (* resume ) (struct ibmvscsi_host_data*) ;} ;

/* Variables and functions */
 struct ibmvscsi_host_data* dev_get_drvdata (struct device*) ; 
 TYPE_1__* ibmvscsi_ops ; 
 int stub1 (struct ibmvscsi_host_data*) ; 

__attribute__((used)) static int ibmvscsi_resume(struct device *dev)
{
	struct ibmvscsi_host_data *hostdata = dev_get_drvdata(dev);
	return ibmvscsi_ops->resume(hostdata);
}