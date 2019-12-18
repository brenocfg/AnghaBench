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
 scalar_t__ UMID_LEN ; 
 int /*<<< orphan*/  printf (char*,char) ; 
 char remove_files_and_dir (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  umid ; 
 char* uml_dir ; 

__attribute__((used)) static void remove_umid_dir(void)
{
	char dir[strlen(uml_dir) + UMID_LEN + 1], err;

	sprintf(dir, "%s%s", uml_dir, umid);
	err = remove_files_and_dir(dir);
	if (err)
		printf("remove_umid_dir - remove_files_and_dir failed with "
		       "err = %d\n", err);
}