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
 int* ccllen ; 
 int* cclmap ; 
 int* ccltbl ; 
 int* ecgroup ; 
 int lastccl ; 

void    ccl2ecl ()
{
	int     i, ich, newlen, cclp, ccls, cclmec;

	for (i = 1; i <= lastccl; ++i) {
		/* We loop through each character class, and for each character
		 * in the class, add the character's equivalence class to the
		 * new "character" class we are creating.  Thus when we are all
		 * done, character classes will really consist of collections
		 * of equivalence classes
		 */

		newlen = 0;
		cclp = cclmap[i];

		for (ccls = 0; ccls < ccllen[i]; ++ccls) {
			ich = ccltbl[cclp + ccls];
			cclmec = ecgroup[ich];

			if (cclmec > 0) {
				ccltbl[cclp + newlen] = cclmec;
				++newlen;
			}
		}

		ccllen[i] = newlen;
	}
}