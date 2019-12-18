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
typedef  int /*<<< orphan*/  vid ;
struct fc_vport_identifiers {int disable; int /*<<< orphan*/  vport_type; int /*<<< orphan*/  roles; int /*<<< orphan*/  node_name; int /*<<< orphan*/  port_name; } ;
struct fc_vport {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  shost_gendev; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FC_PORTTYPE_NPIV ; 
 int /*<<< orphan*/  FC_PORT_ROLE_FCP_INITIATOR ; 
 int fc_parse_wwn (char const*,int /*<<< orphan*/ *) ; 
 int fc_vport_setup (struct Scsi_Host*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct fc_vport_identifiers*,struct fc_vport**) ; 
 int /*<<< orphan*/  memset (struct fc_vport_identifiers*,int /*<<< orphan*/ ,int) ; 
 struct Scsi_Host* transport_class_to_shost (struct device*) ; 

__attribute__((used)) static ssize_t
store_fc_host_vport_create(struct device *dev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct Scsi_Host *shost = transport_class_to_shost(dev);
	struct fc_vport_identifiers vid;
	struct fc_vport *vport;
	unsigned int cnt=count;
	int stat;

	memset(&vid, 0, sizeof(vid));

	/* count may include a LF at end of string */
	if (buf[cnt-1] == '\n')
		cnt--;

	/* validate we have enough characters for WWPN */
	if ((cnt != (16+1+16)) || (buf[16] != ':'))
		return -EINVAL;

	stat = fc_parse_wwn(&buf[0], &vid.port_name);
	if (stat)
		return stat;

	stat = fc_parse_wwn(&buf[17], &vid.node_name);
	if (stat)
		return stat;

	vid.roles = FC_PORT_ROLE_FCP_INITIATOR;
	vid.vport_type = FC_PORTTYPE_NPIV;
	/* vid.symbolic_name is already zero/NULL's */
	vid.disable = false;		/* always enabled */

	/* we only allow support on Channel 0 !!! */
	stat = fc_vport_setup(shost, 0, &shost->shost_gendev, &vid, &vport);
	return stat ? stat : count;
}