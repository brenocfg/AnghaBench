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
#define  CONST 130 
 int GET_CODE (int /*<<< orphan*/ ) ; 
#define  LABEL_REF 129 
#define  SYMBOL_REF 128 
 int /*<<< orphan*/  compute_reloc_for_rtx_1 ; 
 int /*<<< orphan*/  for_each_rtx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
compute_reloc_for_rtx (rtx x)
{
  int reloc;

  switch (GET_CODE (x))
    {
    case CONST:
    case SYMBOL_REF:
    case LABEL_REF:
      reloc = 0;
      for_each_rtx (&x, compute_reloc_for_rtx_1, &reloc);
      return reloc;

    default:
      return 0;
    }
}