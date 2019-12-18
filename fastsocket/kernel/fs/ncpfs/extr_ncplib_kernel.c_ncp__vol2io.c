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
 int ENAMETOOLONG ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char const*,unsigned int) ; 
 unsigned char tolower (unsigned char const) ; 

int
ncp__vol2io(unsigned char *iname, unsigned int *ilen,
		const unsigned char *vname, unsigned int vlen, int cc)
{
	int i;

	if (*ilen <= vlen)
		return -ENAMETOOLONG;

	if (cc)
		for (i = 0; i < vlen; i++) {
			*iname = tolower(*vname);
			iname++;
			vname++;
		}
	else {
		memmove(iname, vname, vlen);
		iname += vlen;
	}

	*ilen = vlen;
	*iname = 0;
	return 0;
}