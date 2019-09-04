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
typedef  int uchar ;
typedef  int chunk ;

/* Variables and functions */
 scalar_t__ BIGENDIAN ; 
 int /*<<< orphan*/ * sboxes ; 
 int /*<<< orphan*/  tiger_compress (int*,int*) ; 

void tiger_gensboxes()
{
	const char *str = "Tiger - A Fast New Hash Function, by Ross Anderson and Eli Biham";
	chunk state[3] = { 0x0123456789ABCDEFULL, 0xFEDCBA9876543210ULL, 0xF096A5B4C3B2E187ULL };
	uchar temp[64];
	int i, j, col, sb, pass;

	if(BIGENDIAN)
	{
		for(j = 0; j < 64; j++)
		{
			temp[j^7] = str[j];
		}
	}
	else 
	{
		for(j = 0; j < 64; j++)
		{
			temp[j] = str[j];
		}
	}

	for(i = 0; i < 1024; i++)
	{
		for(col = 0; col < 8; col++)
		{
			((uchar *)&sboxes[i])[col] = i&0xFF;
		}
	}

	int abc = 2;
	for(pass = 0; pass < 5; pass++)
	{
		for(i = 0; i < 256; i++)
		{
			for(sb = 0; sb < 1024; sb += 256)
			{
				abc++;
				if(abc >= 3) { abc = 0; tiger_compress((chunk *)temp, state); }
				for(col = 0; col < 8; col++)
				{
					uchar val = ((uchar *)&sboxes[sb+i])[col];
					((uchar *)&sboxes[sb+i])[col] = ((uchar *)&sboxes[sb + ((uchar *)&state[abc])[col]])[col];
					((uchar *)&sboxes[sb + ((uchar *)&state[abc])[col]])[col] = val;
				}
			}
		}
	}
}