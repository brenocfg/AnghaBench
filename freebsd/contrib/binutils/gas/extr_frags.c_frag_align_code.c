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
typedef  int /*<<< orphan*/  symbolS ;
typedef  int /*<<< orphan*/  relax_substateT ;
typedef  int /*<<< orphan*/  offsetT ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_MEM_FOR_RS_ALIGN_CODE ; 
 char NOP_OPCODE ; 
 char* frag_var (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rs_align_code ; 

void
frag_align_code (int alignment, int max)
{
  char *p;

  p = frag_var (rs_align_code, MAX_MEM_FOR_RS_ALIGN_CODE, 1,
		(relax_substateT) max, (symbolS *) 0,
		(offsetT) alignment, (char *) 0);
  *p = NOP_OPCODE;
}