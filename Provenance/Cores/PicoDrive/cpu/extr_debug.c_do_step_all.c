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
typedef  int /*<<< orphan*/  tmp ;
struct pdb_cpu {int dummy; } ;

/* Variables and functions */
 int CMDRET_CONT_DO_NEXT ; 
 int CMDRET_DONE ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  get_arg (char*,int,char const*) ; 
 int /*<<< orphan*/  pdb_global_icount ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int do_step_all(struct pdb_cpu *cpu, const char *args)
{
  char tmp[32];
  if (!get_arg(tmp, sizeof(tmp), args)) {
    printf("step_all: missing arg\n");
    return CMDRET_DONE;
  }

  pdb_global_icount = atoi(tmp);
  return CMDRET_CONT_DO_NEXT;
}