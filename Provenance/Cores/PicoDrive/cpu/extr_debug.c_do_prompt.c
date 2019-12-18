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
struct pdb_cpu {int dummy; } ;
typedef  int /*<<< orphan*/  prev ;

/* Variables and functions */
 int do_comands (struct pdb_cpu*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* my_readline (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static void do_prompt(struct pdb_cpu *cpu)
{
  static char prev[128];
  int ret;

  while (1) {
    char *line, *cline;

    line = my_readline("(pdb) ");
    if (line == NULL)
      break;
    if (line[0] == 0)
      cline = prev;
    else {
      cline = line;
      strncpy(prev, line, sizeof(prev));
    }
      
    ret = do_comands(cpu, cline);
    free(line);

    if (ret == 0)
      break;
  }
}