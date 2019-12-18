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

/* Variables and functions */
 int /*<<< orphan*/  CM_ASL_LID ; 
 int /*<<< orphan*/  CM_ASL_PANELPOWER ; 
 int /*<<< orphan*/  CM_ASL_TPD ; 
 int /*<<< orphan*/  CM_ASL_TYPE ; 
 int /*<<< orphan*/  cmsg_quirk (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void cmsg_quirks(void)
{
	cmsg_quirk(CM_ASL_LID, "LID");
	cmsg_quirk(CM_ASL_TYPE, "TYPE");
	cmsg_quirk(CM_ASL_PANELPOWER, "PANELPOWER");
	cmsg_quirk(CM_ASL_TPD, "TPD");
}