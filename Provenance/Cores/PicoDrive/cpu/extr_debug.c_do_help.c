#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pdb_cpu {int dummy; } ;
struct TYPE_3__ {char* cmd; char* help; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int CMDRET_DONE ; 
 TYPE_1__* pdb_cmds ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 

__attribute__((used)) static int do_help(struct pdb_cpu *cpu, const char *args)
{
  int i;
  for (i = 0; i < ARRAY_SIZE(pdb_cmds); i++)
    printf("%s %s\n", pdb_cmds[i].cmd, pdb_cmds[i].help);
  return CMDRET_DONE;
}