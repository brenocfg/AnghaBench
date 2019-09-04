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
union hashval {int* chunks; } ;
typedef  int uchar ;
typedef  int chunk ;

/* Variables and functions */
 scalar_t__ BIGENDIAN ; 
 int /*<<< orphan*/  tiger_compress (int*,int*) ; 
 int /*<<< orphan*/  tiger_gensboxes () ; 

void tiger_hash(const uchar *str, int length, union hashval *val)
{
	static int init = false;
	if(!init) { tiger_gensboxes(); init = true; }

	uchar temp[64];

	val->chunks[0] = 0x0123456789ABCDEFULL;
	val->chunks[1] = 0xFEDCBA9876543210ULL;
	val->chunks[2] = 0xF096A5B4C3B2E187ULL;

	int i, j;
	for(i = length; i >= 64; i -= 64, str += 64)
	{
	    if(BIGENDIAN)
	    {
				for(j = 0; j < 64; j++)
				{
					temp[j^7] = str[j];
				}
				
				tiger_compress((chunk *)temp, val->chunks);
	    }
	    else 
	    {
	    	tiger_compress((chunk *)str, val->chunks);
	    }
	}

	if(BIGENDIAN)
	{
	    for(j = 0; j < i; j++) temp[j^7] = str[j];
	    temp[j^7] = 0x01;
	    while(++j&7) temp[j^7] = 0;
	}
	else
	{
	    for(j = 0; j < i; j++) temp[j] = str[j];
	    temp[j] = 0x01;
	    while(++j&7) temp[j] = 0;
	}

	if(j > 56)
	{
	    while(j < 64) temp[j++] = 0;
	    tiger_compress((chunk *)temp, val->chunks);
	    j = 0;
	}
	while(j < 56) temp[j++] = 0;
	*(chunk *)(temp+56) = (chunk)length<<3;
	tiger_compress((chunk *)temp, val->chunks);
}