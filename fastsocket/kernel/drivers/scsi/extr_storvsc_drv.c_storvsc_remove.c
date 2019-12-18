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
struct storvsc_device {struct Scsi_Host* host; } ;
struct hv_device {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 struct storvsc_device* hv_get_drvdata (struct hv_device*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  storvsc_dev_remove (struct hv_device*) ; 

__attribute__((used)) static int storvsc_remove(struct hv_device *dev)
{
	struct storvsc_device *stor_device = hv_get_drvdata(dev);
	struct Scsi_Host *host = stor_device->host;

	scsi_remove_host(host);
	storvsc_dev_remove(dev);
	scsi_host_put(host);

	return 0;
}