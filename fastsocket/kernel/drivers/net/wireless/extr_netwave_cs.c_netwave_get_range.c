#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int length; } ;
union iwreq_data {TYPE_1__ data; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_4__ {int qual; int level; scalar_t__ noise; } ;
struct iw_range {int we_version_source; int throughput; int min_nwid; int max_nwid; int sensitivity; int num_bitrates; int* bitrate; int* encoding_size; int num_encoding_sizes; int max_encoding_tokens; TYPE_2__ max_qual; scalar_t__ num_frequency; scalar_t__ num_channels; int /*<<< orphan*/  we_version_compiled; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIRELESS_EXT ; 
 int /*<<< orphan*/  memset (struct iw_range*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int netwave_get_range(struct net_device *dev,
			     struct iw_request_info *info,
			     union iwreq_data *wrqu,
			     char *extra)
{
	struct iw_range *range = (struct iw_range *) extra;
	int ret = 0;

	/* Set the length (very important for backward compatibility) */
	wrqu->data.length = sizeof(struct iw_range);

	/* Set all the info we don't care or don't know about to zero */
	memset(range, 0, sizeof(struct iw_range));

	/* Set the Wireless Extension versions */
	range->we_version_compiled = WIRELESS_EXT;
	range->we_version_source = 9;	/* Nothing for us in v10 and v11 */
		   
	/* Set information in the range struct */
	range->throughput = 450 * 1000;	/* don't argue on this ! */
	range->min_nwid = 0x0000;
	range->max_nwid = 0x01FF;

	range->num_channels = range->num_frequency = 0;
		   
	range->sensitivity = 0x3F;
	range->max_qual.qual = 255;
	range->max_qual.level = 255;
	range->max_qual.noise = 0;
		   
	range->num_bitrates = 1;
	range->bitrate[0] = 1000000;	/* 1 Mb/s */

	range->encoding_size[0] = 2;		/* 16 bits scrambling */
	range->num_encoding_sizes = 1;
	range->max_encoding_tokens = 1;	/* Only one key possible */

	return ret;
}