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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  instr ;

/* Variables and functions */
 scalar_t__ baz ; 
 int /*<<< orphan*/  bcopy (int*,int*,int) ; 
 int /*<<< orphan*/  free (int*) ; 
 int* malloc (int) ; 
 int stub1 () ; 

__attribute__((used)) static int
foo(void)
{
	/*
	 * In order to assure that our helper is properly employed to identify
	 * the frame, we're going to trampoline through data.
	 */
	uint32_t instr[] = {
	    0x9de3bfa0,		/* save %sp, -0x60, %sp	*/
	    0x40000000,		/* call baz		*/
	    0x01000000,		/* nop			*/
	    0x81c7e008,		/* ret			*/
	    0x81e80000		/* restore		*/
	};
	uint32_t *fp = malloc(sizeof (instr));

	/*
	 * Do our little relocation dance.
	 */
	instr[1] |= ((uintptr_t)baz - (uintptr_t)&fp[1]) >> 2;

	/*
	 * Copy the code to the heap (it's a pain to build in ON with an
	 * executable stack).
	 */
	bcopy(instr, fp, sizeof (instr));

	(*(int (*)(void))fp)();

	free(fp);

	return (0);
}