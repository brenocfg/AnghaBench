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
 int MAX_MEM_FOR_RS_ALIGN_CODE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_fatal (int /*<<< orphan*/ ) ; 
 char* frag_var (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rs_align_code ; 

void
arm_frag_align_code (int n, int max)
{
  char * p;

  /* We assume that there will never be a requirement
     to support alignments greater than 32 bytes.  */
  if (max > MAX_MEM_FOR_RS_ALIGN_CODE)
    as_fatal (_("alignments greater than 32 bytes not supported in .text sections."));

  p = frag_var (rs_align_code,
		MAX_MEM_FOR_RS_ALIGN_CODE,
		1,
		(relax_substateT) max,
		(symbolS *) NULL,
		(offsetT) n,
		(char *) NULL);
  *p = 0;
}