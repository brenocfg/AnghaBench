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
struct TYPE_2__ {char* sleep_ms; scalar_t__ last_slept; scalar_t__ last_action; scalar_t__ state; scalar_t__ off_override; } ;
struct ar9170 {TYPE_1__ ps; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD (char*,int /*<<< orphan*/ ,size_t,char*,char*) ; 
 scalar_t__ jiffies ; 
 char* jiffies_to_msecs (scalar_t__) ; 

__attribute__((used)) static char *carl9170_debugfs_sta_psm_read(struct ar9170 *ar, char *buf,
					   size_t bufsize, ssize_t *len)
{
	ADD(buf, *len, bufsize, "psm state: %s\n", (ar->ps.off_override ?
	    "FORCE CAM" : (ar->ps.state ? "PSM" : "CAM")));

	ADD(buf, *len, bufsize, "sleep duration: %d ms.\n", ar->ps.sleep_ms);
	ADD(buf, *len, bufsize, "last power-state transition: %d ms ago.\n",
	    jiffies_to_msecs(jiffies - ar->ps.last_action));
	ADD(buf, *len, bufsize, "last CAM->PSM transition: %d ms ago.\n",
	    jiffies_to_msecs(jiffies - ar->ps.last_slept));

	return buf;
}