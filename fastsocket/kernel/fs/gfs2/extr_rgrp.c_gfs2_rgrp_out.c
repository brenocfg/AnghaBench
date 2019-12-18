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
struct gfs2_rgrpd {int rd_flags; int rd_free; int rd_dinodes; int /*<<< orphan*/  rd_igeneration; } ;
struct gfs2_rgrp {int /*<<< orphan*/  rg_reserved; int /*<<< orphan*/  rg_igeneration; void* __pad; void* rg_dinodes; void* rg_free; void* rg_flags; } ;

/* Variables and functions */
 int GFS2_RDF_MASK ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gfs2_rgrp_out(struct gfs2_rgrpd *rgd, void *buf)
{
	struct gfs2_rgrp *str = buf;

	str->rg_flags = cpu_to_be32(rgd->rd_flags & ~GFS2_RDF_MASK);
	str->rg_free = cpu_to_be32(rgd->rd_free);
	str->rg_dinodes = cpu_to_be32(rgd->rd_dinodes);
	str->__pad = cpu_to_be32(0);
	str->rg_igeneration = cpu_to_be64(rgd->rd_igeneration);
	memset(&str->rg_reserved, 0, sizeof(str->rg_reserved));
}