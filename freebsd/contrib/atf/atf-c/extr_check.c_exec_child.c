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
struct exec_data {char** m_argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  const_execvp (char*,char**) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void
exec_child(void *v)
{
    struct exec_data *ea = v;

    const_execvp(ea->m_argv[0], ea->m_argv);
    fprintf(stderr, "execvp(%s) failed: %s\n", ea->m_argv[0], strerror(errno));
    exit(127);
}