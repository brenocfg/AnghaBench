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
typedef  size_t UINT ;
typedef  char UCHAR ;

/* Variables and functions */
 char* Malloc (size_t) ; 
 size_t TRAFFIC_BUF_SIZE ; 
 int rand () ; 

void TtGenerateRandomData(UCHAR **buf, UINT *size)
{
	UCHAR *tmp;
	UINT sz;
	UINT i;
	// Validate arguments
	if (buf == NULL || size == NULL)
	{
		return;
	}

	sz = TRAFFIC_BUF_SIZE;
	tmp = Malloc(sz);
	for (i = 0;i < sz;i++)
	{
		tmp[i] = rand() % 256;

		if (tmp[i] == '!')
		{
			tmp[i] = '_';
		}
	}

	*buf = tmp;
	*size = sz;
}