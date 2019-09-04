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
union hashval {int* bytes; } ;
typedef  int uchar ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  tiger_hash (int*,int /*<<< orphan*/ ,union hashval*) ; 

char *cube2crypto_hashstring(char *string)
{
	char *result = (char *)malloc(49);
	union hashval hv;
	
	tiger_hash((uchar *)string, strlen(string), &hv);
	
	int i;
	for(i = 0; i < sizeof(hv.bytes); i++)
	{
		uchar c = hv.bytes[i];
		*(result+(i*2))   = "0123456789ABCDEF"[c&0xF];
		*(result+(i*2)+1) = "0123456789ABCDEF"[c>>4];
	}
	*(result+(i*2)+2) = '\0';
	
	return result;
}