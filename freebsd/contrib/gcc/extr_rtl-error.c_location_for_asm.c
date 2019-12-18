#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * rtx ;
struct TYPE_5__ {int /*<<< orphan*/  line; int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ location_t ;

/* Variables and functions */
 scalar_t__ ASM_OPERANDS ; 
 int /*<<< orphan*/  ASM_OPERANDS_SOURCE_FILE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASM_OPERANDS_SOURCE_LINE (int /*<<< orphan*/ *) ; 
 TYPE_1__ ASM_OPERANDS_SOURCE_LOCATION (int /*<<< orphan*/ *) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ *) ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/ * PATTERN (int /*<<< orphan*/ *) ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/ * SET_SRC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XVECEXP (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ input_location ; 

__attribute__((used)) static location_t
location_for_asm (rtx insn)
{
  rtx body = PATTERN (insn);
  rtx asmop;
  location_t loc;

  /* Find the (or one of the) ASM_OPERANDS in the insn.  */
  if (GET_CODE (body) == SET && GET_CODE (SET_SRC (body)) == ASM_OPERANDS)
    asmop = SET_SRC (body);
  else if (GET_CODE (body) == ASM_OPERANDS)
    asmop = body;
  else if (GET_CODE (body) == PARALLEL
	   && GET_CODE (XVECEXP (body, 0, 0)) == SET)
    asmop = SET_SRC (XVECEXP (body, 0, 0));
  else if (GET_CODE (body) == PARALLEL
	   && GET_CODE (XVECEXP (body, 0, 0)) == ASM_OPERANDS)
    asmop = XVECEXP (body, 0, 0);
  else
    asmop = NULL;

  if (asmop)
#ifdef USE_MAPPED_LOCATION
    loc = ASM_OPERANDS_SOURCE_LOCATION (asmop);
#else
    {
      loc.file = ASM_OPERANDS_SOURCE_FILE (asmop);
      loc.line = ASM_OPERANDS_SOURCE_LINE (asmop);
    }
#endif
  else
    loc = input_location;
  return loc;
}