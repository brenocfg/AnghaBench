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
struct TYPE_2__ {int fixed; scalar_t__ disabled; int /*<<< orphan*/  value; } ;
union iwreq_data {TYPE_1__ nwid; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  domain ; 

__attribute__((used)) static int netwave_get_nwid(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *wrqu,
			    char *extra)
{
	wrqu->nwid.value = domain;
	wrqu->nwid.disabled = 0;
	wrqu->nwid.fixed = 1;
	return 0;
}