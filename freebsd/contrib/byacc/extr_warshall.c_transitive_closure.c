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
 unsigned int BITS_PER_WORD ; 
 int WORDSIZE (int) ; 

__attribute__((used)) static void
transitive_closure(unsigned *R, int n)
{
    int rowsize;
    unsigned i;
    unsigned *rowj;
    unsigned *rp;
    unsigned *rend;
    unsigned *ccol;
    unsigned *relend;
    unsigned *cword;
    unsigned *rowi;

    rowsize = WORDSIZE(n);
    relend = R + n * rowsize;

    cword = R;
    i = 0;
    rowi = R;
    while (rowi < relend)
    {
	ccol = cword;
	rowj = R;

	while (rowj < relend)
	{
	    if (*ccol & (unsigned)(1 << i))
	    {
		rp = rowi;
		rend = rowj + rowsize;
		while (rowj < rend)
		    *rowj++ |= *rp++;
	    }
	    else
	    {
		rowj += rowsize;
	    }

	    ccol += rowsize;
	}

	if (++i >= BITS_PER_WORD)
	{
	    i = 0;
	    cword++;
	}

	rowi += rowsize;
    }
}