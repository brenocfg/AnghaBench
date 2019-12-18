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
struct TYPE_2__ {int ipv6_options; } ;
struct scsi_qla_host {TYPE_1__ ip_config; } ;

/* Variables and functions */
 int IPV6_OPT_IPV6_PROTOCOL_ENABLE ; 

__attribute__((used)) static inline int is_ipv6_enabled(struct scsi_qla_host *ha)
{
	return ((ha->ip_config.ipv6_options &
		IPV6_OPT_IPV6_PROTOCOL_ENABLE) != 0);
}