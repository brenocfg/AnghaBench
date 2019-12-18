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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int fread (void*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,void*,int) ; 

__attribute__((used)) static int read_to_upper(void *dest, void *tmpbuf, int tmpsize, FILE *f)
{
	int nRead, nLen = 0;

	while(1)
	{
		nRead = fread(tmpbuf, 1, tmpsize, f);
		if(nRead <= 0)
			break;
		memcpy((unsigned char *)dest + nLen, tmpbuf, nRead);
		nLen += nRead;
	}

	return nLen;
}