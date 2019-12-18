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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * popen (char const*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static char *read_from_shell_command(char *result, size_t sizeof_result, const char *command)
{
    FILE *fp;
    char *pnt;

    if ((fp = popen(command, "r")) == NULL) {
        return NULL;
    }
    if (fgets(result, (int) sizeof_result, fp) == NULL) {
        pclose(fp);
        fprintf(stderr, "Command [%s] failed]\n", command);
        return NULL;
    }
    if ((pnt = strrchr(result, '\n')) != NULL) {
        *pnt = 0;
    }
    (void) pclose(fp);

    return *result == 0 ? NULL : result;
}