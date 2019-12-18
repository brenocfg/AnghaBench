#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct decision_head {TYPE_1__* first; } ;
typedef  enum routine_type { ____Placeholder_routine_type } routine_type ;
struct TYPE_2__ {int subroutine_number; } ;

/* Variables and functions */
 scalar_t__ IS_SPLIT (int) ; 
#define  PEEPHOLE2 130 
#define  RECOG 129 
#define  SPLIT 128 
 int max_depth ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  write_tree (struct decision_head*,char*,int,int) ; 

__attribute__((used)) static void
write_subroutine (struct decision_head *head, enum routine_type type)
{
  int subfunction = head->first ? head->first->subroutine_number : 0;
  const char *s_or_e;
  char extension[32];
  int i;

  s_or_e = subfunction ? "static " : "";

  if (subfunction)
    sprintf (extension, "_%d", subfunction);
  else if (type == RECOG)
    extension[0] = '\0';
  else
    strcpy (extension, "_insns");

  switch (type)
    {
    case RECOG:
      printf ("%sint\n\
recog%s (rtx x0 ATTRIBUTE_UNUSED,\n\trtx insn ATTRIBUTE_UNUSED,\n\tint *pnum_clobbers ATTRIBUTE_UNUSED)\n", s_or_e, extension);
      break;
    case SPLIT:
      printf ("%srtx\n\
split%s (rtx x0 ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)\n",
	      s_or_e, extension);
      break;
    case PEEPHOLE2:
      printf ("%srtx\n\
peephole2%s (rtx x0 ATTRIBUTE_UNUSED,\n\trtx insn ATTRIBUTE_UNUSED,\n\tint *_pmatch_len ATTRIBUTE_UNUSED)\n",
	      s_or_e, extension);
      break;
    }

  printf ("{\n  rtx * const operands ATTRIBUTE_UNUSED = &recog_data.operand[0];\n");
  for (i = 1; i <= max_depth; i++)
    printf ("  rtx x%d ATTRIBUTE_UNUSED;\n", i);

  printf ("  %s tem ATTRIBUTE_UNUSED;\n", IS_SPLIT (type) ? "rtx" : "int");

  if (!subfunction)
    printf ("  recog_data.insn = NULL_RTX;\n");

  if (head->first)
    write_tree (head, "", type, 1);
  else
    printf ("  goto ret0;\n");

  printf (" ret0:\n  return %d;\n}\n\n", IS_SPLIT (type) ? 0 : -1);
}