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
struct lm_lockops {char* lm_proto_name; } ;
struct TYPE_2__ {struct lm_lockops* ls_ops; } ;
struct gfs2_sbd {TYPE_1__ sd_lockstruct; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t proto_name_show(struct gfs2_sbd *sdp, char *buf)
{
	const struct lm_lockops *ops = sdp->sd_lockstruct.ls_ops;
	return sprintf(buf, "%s\n", ops->lm_proto_name);
}