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
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_2__ {int level; int noise; scalar_t__ qual; } ;
struct iw_range {int we_version_source; double throughput; int num_bitrates; int* bitrate; TYPE_1__ max_qual; scalar_t__ num_frequency; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  we_version_compiled; } ;
struct iw_point {int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIRELESS_EXT ; 
 scalar_t__ country ; 
 int /*<<< orphan*/ * hop_pattern_length ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ray_get_range(struct net_device *dev,
			 struct iw_request_info *info,
			 struct iw_point *dwrq, char *extra)
{
	struct iw_range *range = (struct iw_range *)extra;

	memset((char *)range, 0, sizeof(struct iw_range));

	/* Set the length (very important for backward compatibility) */
	dwrq->length = sizeof(struct iw_range);

	/* Set the Wireless Extension versions */
	range->we_version_compiled = WIRELESS_EXT;
	range->we_version_source = 9;

	/* Set information in the range struct */
	range->throughput = 1.1 * 1000 * 1000;	/* Put the right number here */
	range->num_channels = hop_pattern_length[(int)country];
	range->num_frequency = 0;
	range->max_qual.qual = 0;
	range->max_qual.level = 255;	/* What's the correct value ? */
	range->max_qual.noise = 255;	/* Idem */
	range->num_bitrates = 2;
	range->bitrate[0] = 1000000;	/* 1 Mb/s */
	range->bitrate[1] = 2000000;	/* 2 Mb/s */
	return 0;
}