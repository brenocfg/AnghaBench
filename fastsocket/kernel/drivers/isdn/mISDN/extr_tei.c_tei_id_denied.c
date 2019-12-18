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
typedef  int u_char ;
struct TYPE_2__ {int /*<<< orphan*/  (* printdebug ) (struct FsmInst*,char*,int,int) ;} ;
struct teimgr {TYPE_1__ tei_m; } ;
struct FsmInst {struct teimgr* userdata; } ;

/* Variables and functions */
 int DEBUG_L2_TEI ; 
 int* debug ; 
 int /*<<< orphan*/  stub1 (struct FsmInst*,char*,int,int) ; 

__attribute__((used)) static void
tei_id_denied(struct FsmInst *fi, int event, void *arg)
{
	struct teimgr *tm = fi->userdata;
	u_char *dp = arg;
	int ri, tei;

	ri = ((unsigned int) *dp++ << 8);
	ri += *dp++;
	dp++;
	tei = *dp >> 1;
	if (*debug & DEBUG_L2_TEI)
		tm->tei_m.printdebug(fi, "identity denied ri %d tei %d",
			ri, tei);
}