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
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  AtoH (char*,char*,int) ; 
 int ETH_MAC_ADDR_STR_LEN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  isxdigit (char) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 

BOOLEAN rtstrmactohex(char *s1, char *s2)
{
	int i = 0;
	char *ptokS = s1, *ptokE = s1;

	if (strlen(s1) != ETH_MAC_ADDR_STR_LEN)
		return FALSE;

	while((*ptokS) != '\0')
	{
		if((ptokE = strchr(ptokS, ':')) != NULL)
			*ptokE++ = '\0';
		if ((strlen(ptokS) != 2) || (!isxdigit(*ptokS)) || (!isxdigit(*(ptokS+1))))
			break; // fail
		AtoH(ptokS, &s2[i++], 1);
		ptokS = ptokE;
		if (i == 6)
			break; // parsing finished
	}

	return ( i == 6 ? TRUE : FALSE);

}