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
 int WCONTINUED ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int WUNTRACED ; 
 int /*<<< orphan*/  execlp (char*,char*,char*,int /*<<< orphan*/ *) ; 
 int fork () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  waitpid (int,int*,int) ; 

int validate_desktop_file(char *file) {
    int statval;
    int child_pid;
    child_pid = fork();
    if(child_pid == -1)
    {
        printf("could not fork! \n");
        return 1;
    }
    else if(child_pid == 0)
    {
        execlp("desktop-file-validate", "desktop-file-validate", file, NULL);
    }
    else
    {
        waitpid(child_pid, &statval, WUNTRACED | WCONTINUED);
        if(WIFEXITED(statval)){
            return(WEXITSTATUS(statval));
        }
    }
    return -1;
}