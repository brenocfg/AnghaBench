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
struct powertec_info {scalar_t__ term_ctl; } ;
struct expansion_card {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct expansion_card* ECARD_DEV (struct device*) ; 
 struct Scsi_Host* ecard_get_drvdata (struct expansion_card*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t powertecscsi_show_term(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct expansion_card *ec = ECARD_DEV(dev);
	struct Scsi_Host *host = ecard_get_drvdata(ec);
	struct powertec_info *info = (struct powertec_info *)host->hostdata;

	return sprintf(buf, "%d\n", info->term_ctl ? 1 : 0);
}