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
typedef  int u32 ;
struct gfs2_ea_header {int ea_flags; void* ea_rec_len; } ;

/* Variables and functions */
 int GFS2_EAFLAG_LAST ; 
 int GFS2_EA_REC_LEN (struct gfs2_ea_header*) ; 
 int GFS2_EA_SIZE (struct gfs2_ea_header*) ; 
 void* cpu_to_be32 (int) ; 

__attribute__((used)) static struct gfs2_ea_header *ea_split_ea(struct gfs2_ea_header *ea)
{
	u32 ea_size = GFS2_EA_SIZE(ea);
	struct gfs2_ea_header *new = (struct gfs2_ea_header *)((char *)ea +
				     ea_size);
	u32 new_size = GFS2_EA_REC_LEN(ea) - ea_size;
	int last = ea->ea_flags & GFS2_EAFLAG_LAST;

	ea->ea_rec_len = cpu_to_be32(ea_size);
	ea->ea_flags ^= last;

	new->ea_rec_len = cpu_to_be32(new_size);
	new->ea_flags = last;

	return new;
}