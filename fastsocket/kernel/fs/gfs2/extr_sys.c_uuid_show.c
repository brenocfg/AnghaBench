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
typedef  int u8 ;
struct TYPE_2__ {int* sb_uuid; } ;
struct gfs2_sbd {TYPE_1__ sd_sb; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  gfs2_uuid_valid (int const*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const) ; 

__attribute__((used)) static ssize_t uuid_show(struct gfs2_sbd *sdp, char *buf)
{
	const u8 *uuid = sdp->sd_sb.sb_uuid;
	buf[0] = '\0';
	if (!gfs2_uuid_valid(uuid))
		return 0;
	return snprintf(buf, PAGE_SIZE, "%02X%02X%02X%02X-%02X%02X-"
			"%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X\n",
			uuid[0], uuid[1], uuid[2], uuid[3], uuid[4], uuid[5],
			uuid[6], uuid[7], uuid[8], uuid[9], uuid[10], uuid[11],
			uuid[12], uuid[13], uuid[14], uuid[15]);
}