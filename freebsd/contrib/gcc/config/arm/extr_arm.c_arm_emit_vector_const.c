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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ CONST_VECTOR ; 
 int /*<<< orphan*/  CONST_VECTOR_ELT (int /*<<< orphan*/ ,int) ; 
 int CONST_VECTOR_NUNITS (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTVAL (int /*<<< orphan*/ ) ; 
#define  V2SImode 130 
#define  V4HImode 129 
#define  V8QImode 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char const*,...) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

int
arm_emit_vector_const (FILE *file, rtx x)
{
  int i;
  const char * pattern;

  gcc_assert (GET_CODE (x) == CONST_VECTOR);

  switch (GET_MODE (x))
    {
    case V2SImode: pattern = "%08x"; break;
    case V4HImode: pattern = "%04x"; break;
    case V8QImode: pattern = "%02x"; break;
    default:       gcc_unreachable ();
    }

  fprintf (file, "0x");
  for (i = CONST_VECTOR_NUNITS (x); i--;)
    {
      rtx element;

      element = CONST_VECTOR_ELT (x, i);
      fprintf (file, pattern, INTVAL (element));
    }

  return 1;
}