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
typedef  int /*<<< orphan*/  status ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_string (char const*) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 char* sprintf_dup (char*,char const*) ; 

__attribute__((used)) static int overlay_applied(const char *overlay_dir)
{
    char status[7] = { '\0' };
    const char *status_path = sprintf_dup("%s/status", overlay_dir);
    FILE *fp = fopen(status_path, "r");
    int bytes = 0;
    if (fp)
    {
	bytes = fread(status, 1, sizeof(status), fp);
	fclose(fp);
    }
    free_string(status_path);
    return (bytes == sizeof(status)) &&
	(memcmp(status, "applied", sizeof(status)) == 0);
}