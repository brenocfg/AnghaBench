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
 int /*<<< orphan*/  RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY ; 
 char* SLASH ; 
 scalar_t__ environ_cb (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*,char const*,...) ; 

__attribute__((used)) static void make_system_path(char *buf, size_t buf_size,
	const char *name, const char *ext)
{
	const char *dir = NULL;

	if (environ_cb(RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY, &dir) && dir) {
		snprintf(buf, buf_size, "%s%c%s%s", dir, SLASH, name, ext);
	}
	else {
		snprintf(buf, buf_size, "%s%s", name, ext);
	}
}