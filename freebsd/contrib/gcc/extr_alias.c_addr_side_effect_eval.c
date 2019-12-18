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
 int /*<<< orphan*/  GEN_INT (int) ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
#define  POST_DEC 131 
#define  POST_INC 130 
#define  PRE_DEC 129 
#define  PRE_INC 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  canon_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PLUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
addr_side_effect_eval (rtx addr, int size, int n_refs)
{
  int offset = 0;

  switch (GET_CODE (addr))
    {
    case PRE_INC:
      offset = (n_refs + 1) * size;
      break;
    case PRE_DEC:
      offset = -(n_refs + 1) * size;
      break;
    case POST_INC:
      offset = n_refs * size;
      break;
    case POST_DEC:
      offset = -n_refs * size;
      break;

    default:
      return addr;
    }

  if (offset)
    addr = gen_rtx_PLUS (GET_MODE (addr), XEXP (addr, 0),
			 GEN_INT (offset));
  else
    addr = XEXP (addr, 0);
  addr = canon_rtx (addr);

  return addr;
}