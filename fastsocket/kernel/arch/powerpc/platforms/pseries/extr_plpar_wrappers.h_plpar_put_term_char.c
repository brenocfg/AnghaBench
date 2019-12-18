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

/* Variables and functions */
 int /*<<< orphan*/  H_PUT_TERM_CHAR ; 
 long plpar_hcall_norets (int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static inline long plpar_put_term_char(unsigned long termno, unsigned long len,
		const char *buffer)
{
	unsigned long *lbuf = (unsigned long *)buffer;	/* TODO: alignment? */
	return plpar_hcall_norets(H_PUT_TERM_CHAR, termno, len, lbuf[0],
			lbuf[1]);
}