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
typedef  int byte ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int MAX_MAP_LEAFS ; 
 int /*<<< orphan*/  _printf (char*,...) ; 
 int leafbytes ; 
 int leaflongs ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int portalclusters ; 
 int* visBytes ; 

void CalcPHS (void)
{
	int		i, j, k, l, index;
	int		bitbyte;
	long	*dest, *src;
	byte	*scan;
	int		count;
	byte	uncompressed[MAX_MAP_LEAFS/8];

	_printf ("Building PHS...\n");

	count = 0;
	for (i=0 ; i<portalclusters ; i++)
	{
		scan = visBytes + i*leafbytes;
		memcpy (uncompressed, scan, leafbytes);
		for (j=0 ; j<leafbytes ; j++)
		{
			bitbyte = scan[j];
			if (!bitbyte)
				continue;
			for (k=0 ; k<8 ; k++)
			{
				if (! (bitbyte & (1<<k)) )
					continue;
				// OR this pvs row into the phs
				index = ((j<<3)+k);
				if (index >= portalclusters)
					Error ("Bad bit in PVS");	// pad bits should be 0
				src = (long *)(visBytes + index*leafbytes);
				dest = (long *)uncompressed;
				for (l=0 ; l<leaflongs ; l++)
					((long *)uncompressed)[l] |= src[l];
			}
		}
		for (j=0 ; j<portalclusters ; j++)
			if (uncompressed[j>>3] & (1<<(j&7)) )
				count++;

		// FIXME: copy it off
	}

	_printf ("Average clusters hearable: %i\n", count/portalclusters);
}