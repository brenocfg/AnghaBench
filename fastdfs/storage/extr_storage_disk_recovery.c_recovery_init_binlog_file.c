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
 int MAX_PATH_SIZE ; 
 int /*<<< orphan*/  recovery_get_binlog_filename (char const*,char*) ; 
 int writeToFile (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int recovery_init_binlog_file(const char *pBasePath)
{
	char full_binlog_filename[MAX_PATH_SIZE];
	char buff[1];

	*buff = '\0';
	recovery_get_binlog_filename(pBasePath, full_binlog_filename);
	return writeToFile(full_binlog_filename, buff, 0);
}