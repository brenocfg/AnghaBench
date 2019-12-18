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
struct TYPE_2__ {char* smk_known; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_MAC_OVERRIDE ; 
 int EACCES ; 
 int cap_syslog (int) ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 char* current_security () ; 
 TYPE_1__ smack_known_floor ; 

__attribute__((used)) static int smack_syslog(int type)
{
	int rc;
	char *sp = current_security();

	rc = cap_syslog(type);
	if (rc != 0)
		return rc;

	if (capable(CAP_MAC_OVERRIDE))
		return 0;

	 if (sp != smack_known_floor.smk_known)
		rc = -EACCES;

	return rc;
}