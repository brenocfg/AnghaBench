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
struct trackpoint_data {int /*<<< orphan*/  ext_dev; int /*<<< orphan*/  skipback; int /*<<< orphan*/  inertia; int /*<<< orphan*/  jenks; int /*<<< orphan*/  ztime; int /*<<< orphan*/  upthresh; int /*<<< orphan*/  thresh; int /*<<< orphan*/  mindrag; int /*<<< orphan*/  draghys; int /*<<< orphan*/  reach; int /*<<< orphan*/  speed; int /*<<< orphan*/  sensitivity; int /*<<< orphan*/  press_to_select; } ;

/* Variables and functions */
 int /*<<< orphan*/  TP_DEF_DRAGHYS ; 
 int /*<<< orphan*/  TP_DEF_EXT_DEV ; 
 int /*<<< orphan*/  TP_DEF_INERTIA ; 
 int /*<<< orphan*/  TP_DEF_JENKS_CURV ; 
 int /*<<< orphan*/  TP_DEF_MINDRAG ; 
 int /*<<< orphan*/  TP_DEF_PTSON ; 
 int /*<<< orphan*/  TP_DEF_REACH ; 
 int /*<<< orphan*/  TP_DEF_SENS ; 
 int /*<<< orphan*/  TP_DEF_SKIPBACK ; 
 int /*<<< orphan*/  TP_DEF_SPEED ; 
 int /*<<< orphan*/  TP_DEF_THRESH ; 
 int /*<<< orphan*/  TP_DEF_UP_THRESH ; 
 int /*<<< orphan*/  TP_DEF_Z_TIME ; 

__attribute__((used)) static void trackpoint_defaults(struct trackpoint_data *tp)
{
	tp->press_to_select = TP_DEF_PTSON;
	tp->sensitivity = TP_DEF_SENS;
	tp->speed = TP_DEF_SPEED;
	tp->reach = TP_DEF_REACH;

	tp->draghys = TP_DEF_DRAGHYS;
	tp->mindrag = TP_DEF_MINDRAG;

	tp->thresh = TP_DEF_THRESH;
	tp->upthresh = TP_DEF_UP_THRESH;

	tp->ztime = TP_DEF_Z_TIME;
	tp->jenks = TP_DEF_JENKS_CURV;

	tp->inertia = TP_DEF_INERTIA;
	tp->skipback = TP_DEF_SKIPBACK;
	tp->ext_dev = TP_DEF_EXT_DEV;
}