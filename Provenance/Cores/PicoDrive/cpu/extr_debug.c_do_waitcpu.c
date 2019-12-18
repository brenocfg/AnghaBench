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
struct pdb_cpu {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int CMDRET_CONT_REDO ; 
 int CMDRET_DONE ; 
 int /*<<< orphan*/  get_arg (char*,int,char const*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_waitcpu(struct pdb_cpu *cpu, const char *args)
{
  char tmp[32];
  if (!get_arg(tmp, sizeof(tmp), args)) {
    printf("waitcpu: missing arg\n");
    return CMDRET_DONE;
  }
  if (strcmp(tmp, cpu->name) == 0)
    return CMDRET_DONE;

  return CMDRET_CONT_REDO;
}