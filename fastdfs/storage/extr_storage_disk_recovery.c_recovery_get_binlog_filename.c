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
 int /*<<< orphan*/  RECOVERY_BINLOG_FILENAME ; 
 char* recovery_get_full_filename (void const*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *recovery_get_binlog_filename(const void *pArg, \
                        char *full_filename)
{
	return recovery_get_full_filename(pArg, \
			RECOVERY_BINLOG_FILENAME, full_filename);
}