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
struct gru_state {int /*<<< orphan*/  gs_asid_gen; int /*<<< orphan*/  gs_gid; } ;

/* Variables and functions */
 int MIN_ASID ; 
 int /*<<< orphan*/  STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asid_wrap ; 
 int /*<<< orphan*/  gru_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grudev ; 

__attribute__((used)) static int gru_wrap_asid(struct gru_state *gru)
{
	gru_dbg(grudev, "gid %d\n", gru->gs_gid);
	STAT(asid_wrap);
	gru->gs_asid_gen++;
	return MIN_ASID;
}