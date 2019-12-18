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
 int ISDN_MSNLEN ; 
 int isdn_wildmat (char*,char*) ; 

int isdn_msncmp( const char * msn1, const char * msn2 )
{
	char TmpMsn1[ ISDN_MSNLEN ];
	char TmpMsn2[ ISDN_MSNLEN ];
	char *p;

	for ( p = TmpMsn1; *msn1 && *msn1 != ':'; )  // Strip off a SPID
		*p++ = *msn1++;
	*p = '\0';

	for ( p = TmpMsn2; *msn2 && *msn2 != ':'; )  // Strip off a SPID
		*p++ = *msn2++;
	*p = '\0';

	return isdn_wildmat( TmpMsn1, TmpMsn2 );
}