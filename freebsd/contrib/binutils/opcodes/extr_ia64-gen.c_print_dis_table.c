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
struct disent {int completer_index; int insn; int priority; struct disent* next_ent; struct disent* nexte; } ;

/* Variables and functions */
 struct disent* disinsntable ; 
 int* insn_list ; 
 int insn_list_len ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_dis_table (void)
{
  int x;
  struct disent *cent = disinsntable;

  printf ("static const char dis_table[] = {\n");
  for (x = 0; x < insn_list_len; x++)
    {
      if ((x > 0) && ((x % 12) == 0))
	printf ("\n");

      printf ("0x%02x, ", insn_list[x]);
    }
  printf ("\n};\n\n");

  printf ("static const struct ia64_dis_names ia64_dis_names[] = {\n");
  while (cent != NULL)
    {
      struct disent *ent = cent;

      while (ent != NULL)
	{
	  printf ("{ 0x%x, %d, %d, %d },\n", ent->completer_index,
		  ent->insn, (ent->nexte != NULL ? 1 : 0),
                  ent->priority);
	  ent = ent->nexte;
	}
      cent = cent->next_ent;
    }
  printf ("};\n\n");
}