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
struct FsmInst {struct Channel* userdata; } ;
struct Channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lli_start_disc (struct FsmInst*,int,void*) ; 
 int /*<<< orphan*/  release_b_st (struct Channel*) ; 

__attribute__((used)) static void
lli_rel_b_disc(struct FsmInst *fi, int event, void *arg)
{
	struct Channel *chanp = fi->userdata;

	release_b_st(chanp);
	lli_start_disc(fi, event, arg);
}