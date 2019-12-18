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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
#define  ADDR_DIFF_VEC 141 
#define  ADDR_VEC 140 
#define  ASM_INPUT 139 
 int BUF_LEN ; 
#define  CALL 138 
#define  CLOBBER 137 
#define  COND_EXEC 136 
 int /*<<< orphan*/  COND_EXEC_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COND_EXEC_TEST (int /*<<< orphan*/ ) ; 
 int EQ ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int NE ; 
#define  PARALLEL 135 
#define  RETURN 134 
#define  SEQUENCE 133 
#define  SET 132 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRAP_CONDITION (int /*<<< orphan*/ ) ; 
#define  TRAP_IF 131 
#define  UNSPEC 130 
#define  UNSPEC_VOLATILE 129 
#define  USE 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 char* XSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  print_exp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_value (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void
print_pattern (char *buf, rtx x, int verbose)
{
  char t1[BUF_LEN], t2[BUF_LEN], t3[BUF_LEN];

  switch (GET_CODE (x))
    {
    case SET:
      print_value (t1, SET_DEST (x), verbose);
      print_value (t2, SET_SRC (x), verbose);
      sprintf (buf, "%s=%s", t1, t2);
      break;
    case RETURN:
      sprintf (buf, "return");
      break;
    case CALL:
      print_exp (buf, x, verbose);
      break;
    case CLOBBER:
      print_value (t1, XEXP (x, 0), verbose);
      sprintf (buf, "clobber %s", t1);
      break;
    case USE:
      print_value (t1, XEXP (x, 0), verbose);
      sprintf (buf, "use %s", t1);
      break;
    case COND_EXEC:
      if (GET_CODE (COND_EXEC_TEST (x)) == NE
	  && XEXP (COND_EXEC_TEST (x), 1) == const0_rtx)
	print_value (t1, XEXP (COND_EXEC_TEST (x), 0), verbose);
      else if (GET_CODE (COND_EXEC_TEST (x)) == EQ
	       && XEXP (COND_EXEC_TEST (x), 1) == const0_rtx)
	{
	  t1[0] = '!';
	  print_value (t1 + 1, XEXP (COND_EXEC_TEST (x), 0), verbose);
	}
      else
	print_value (t1, COND_EXEC_TEST (x), verbose);
      print_pattern (t2, COND_EXEC_CODE (x), verbose);
      sprintf (buf, "(%s) %s", t1, t2);
      break;
    case PARALLEL:
      {
	int i;

	sprintf (t1, "{");
	for (i = 0; i < XVECLEN (x, 0); i++)
	  {
	    print_pattern (t2, XVECEXP (x, 0, i), verbose);
	    sprintf (t3, "%s%s;", t1, t2);
	    strcpy (t1, t3);
	  }
	sprintf (buf, "%s}", t1);
      }
      break;
    case SEQUENCE:
      /* Should never see SEQUENCE codes until after reorg.  */
      gcc_unreachable ();
    case ASM_INPUT:
      sprintf (buf, "asm {%s}", XSTR (x, 0));
      break;
    case ADDR_VEC:
      break;
    case ADDR_DIFF_VEC:
      print_value (buf, XEXP (x, 0), verbose);
      break;
    case TRAP_IF:
      print_value (t1, TRAP_CONDITION (x), verbose);
      sprintf (buf, "trap_if %s", t1);
      break;
    case UNSPEC:
      {
	int i;

	sprintf (t1, "unspec{");
	for (i = 0; i < XVECLEN (x, 0); i++)
	  {
	    print_pattern (t2, XVECEXP (x, 0, i), verbose);
	    sprintf (t3, "%s%s;", t1, t2);
	    strcpy (t1, t3);
	  }
	sprintf (buf, "%s}", t1);
      }
      break;
    case UNSPEC_VOLATILE:
      {
	int i;

	sprintf (t1, "unspec/v{");
	for (i = 0; i < XVECLEN (x, 0); i++)
	  {
	    print_pattern (t2, XVECEXP (x, 0, i), verbose);
	    sprintf (t3, "%s%s;", t1, t2);
	    strcpy (t1, t3);
	  }
	sprintf (buf, "%s}", t1);
      }
      break;
    default:
      print_value (buf, x, verbose);
    }
}