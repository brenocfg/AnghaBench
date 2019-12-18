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
struct mca_device {int status; } ;
typedef  enum MCA_AdapterStatus { ____Placeholder_MCA_AdapterStatus } MCA_AdapterStatus ;

/* Variables and functions */

enum MCA_AdapterStatus mca_device_status(struct mca_device *mca_dev)
{
	return mca_dev->status;
}