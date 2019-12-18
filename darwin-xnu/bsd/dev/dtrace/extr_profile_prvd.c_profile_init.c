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
typedef  int /*<<< orphan*/  dev_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROFILE_MAJOR ; 
 int cdevsw_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  profile_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  profile_cdevsw ; 

void profile_init( void )
{
	int majdevno = cdevsw_add(PROFILE_MAJOR, &profile_cdevsw);

	if (majdevno < 0) {
		printf("profile_init: failed to allocate a major number!\n");
		return;
	}

	profile_attach( (dev_info_t*)(uintptr_t)majdevno);
}