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
struct gfs2_ea_header {int ea_type; int /*<<< orphan*/  ea_name_len; } ;

/* Variables and functions */
#define  GFS2_EATYPE_SECURITY 130 
#define  GFS2_EATYPE_SYS 129 
#define  GFS2_EATYPE_USR 128 

__attribute__((used)) static inline unsigned int gfs2_ea_strlen(struct gfs2_ea_header *ea)
{
	switch (ea->ea_type) {
	case GFS2_EATYPE_USR:
		return 5 + ea->ea_name_len + 1;
	case GFS2_EATYPE_SYS:
		return 7 + ea->ea_name_len + 1;
	case GFS2_EATYPE_SECURITY:
		return 9 + ea->ea_name_len + 1;
	default:
		return 0;
	}
}