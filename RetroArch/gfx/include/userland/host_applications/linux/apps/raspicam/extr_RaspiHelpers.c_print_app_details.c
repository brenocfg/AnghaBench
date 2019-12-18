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
 char* GIT_COMMIT_ID ; 
 int /*<<< orphan*/  TAINTED ; 
 char* app_name ; 
 char* basename (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ ) ; 

void print_app_details(FILE *fd)
{
   if (!app_name)
      app_name = "Un-named";

   fprintf(fd, "\n\"%s\" Camera App (commit %s%s)\n\n", basename(app_name), GIT_COMMIT_ID, TAINTED);
}