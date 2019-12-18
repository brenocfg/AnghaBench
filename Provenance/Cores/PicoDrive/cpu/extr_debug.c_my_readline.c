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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_history (char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 char* readline (char*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static char *my_readline(const char *prompt)
{
  char *line = NULL;

#ifdef HAVE_READLINE
  line = readline("(pdb) ");
  if (line == NULL)
    return NULL;
  if (line[0] != 0)
    add_history(line);
#else
  size_t size = 0;
  ssize_t ret;

  printf("(pdb) ");
  fflush(stdout);
  ret = getline(&line, &size, stdin);
  if (ret < 0)
    return NULL;
  if (ret > 0 && line[ret - 1] == '\n')
    line[ret - 1] = 0;
#endif

  return line;
}