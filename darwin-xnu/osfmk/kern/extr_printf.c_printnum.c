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
 int MAXBUF ; 
 int /*<<< orphan*/ * digs ; 
 void stub1 (int,void*) ; 

__attribute__((used)) static int
printnum(
	unsigned long long int	u,	/* number to print */
	int		base,
	void			(*putc)(int, void *),
	void                    *arg)
{
	char	buf[MAXBUF];	/* build number here */
	char *	p = &buf[MAXBUF-1];
	int nprinted = 0;

	do {
	    *p-- = digs[u % base];
	    u /= base;
	} while (u != 0);

	while (++p != &buf[MAXBUF]) {
	    (*putc)(*p, arg);
	    nprinted++;
	}

	return nprinted;
}