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
struct pcd_unit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdelay (int) ; 
 int pcd_command (struct pcd_unit*,char*,int,char*) ; 
 int pcd_completion (struct pcd_unit*,char*,char*) ; 
 int /*<<< orphan*/  pcd_req_sense (struct pcd_unit*,char*) ; 

__attribute__((used)) static int pcd_atapi(struct pcd_unit *cd, char *cmd, int dlen, char *buf, char *fun)
{
	int r;

	r = pcd_command(cd, cmd, dlen, fun);
	mdelay(1);
	if (!r)
		r = pcd_completion(cd, buf, fun);
	if (r)
		pcd_req_sense(cd, fun);

	return r;
}