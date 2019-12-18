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
typedef  int /*<<< orphan*/  u32 ;
struct gfs2_sbd {int dummy; } ;
struct TYPE_2__ {void* mh_format; void* mh_type; void* mh_magic; } ;
struct gfs2_log_descriptor {int /*<<< orphan*/  ld_reserved; scalar_t__ ld_data2; scalar_t__ ld_data1; scalar_t__ ld_length; void* ld_type; TYPE_1__ ld_header; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_FORMAT_LD ; 
 int /*<<< orphan*/  GFS2_MAGIC ; 
 int /*<<< orphan*/  GFS2_METATYPE_LD ; 
 struct gfs2_log_descriptor* bh_log_desc (struct buffer_head*) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct buffer_head* gfs2_log_get_buf (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct buffer_head *gfs2_get_log_desc(struct gfs2_sbd *sdp, u32 ld_type)
{
	struct buffer_head *bh = gfs2_log_get_buf(sdp);
	struct gfs2_log_descriptor *ld = bh_log_desc(bh);
	ld->ld_header.mh_magic = cpu_to_be32(GFS2_MAGIC);
	ld->ld_header.mh_type = cpu_to_be32(GFS2_METATYPE_LD);
	ld->ld_header.mh_format = cpu_to_be32(GFS2_FORMAT_LD);
	ld->ld_type = cpu_to_be32(ld_type);
	ld->ld_length = 0;
	ld->ld_data1 = 0;
	ld->ld_data2 = 0;
	memset(ld->ld_reserved, 0, sizeof(ld->ld_reserved));
	return bh;
}