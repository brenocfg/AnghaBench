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
typedef  int uid_t ;

/* Variables and functions */
 scalar_t__ ENOSYS ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  info (char*,...) ; 
 int kpersona_get (int*) ; 

__attribute__((used)) static int persona_op_support(void)
{
	uid_t pna_id = -1;
	int ret = kpersona_get(&pna_id);
	if (ret == 0 || errno != ENOSYS) {
		info("Persona subsystem is supported (id=%d)", pna_id);
		return 0;
	}

	info("Persona subsystem is not supported");
	return ENOSYS;
}