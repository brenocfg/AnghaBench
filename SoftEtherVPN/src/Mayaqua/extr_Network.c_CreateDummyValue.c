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
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int HTTP_PACK_RAND_SIZE_MAX ; 
 int /*<<< orphan*/ * Malloc (int) ; 
 int /*<<< orphan*/  PackAddData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Rand (int /*<<< orphan*/ *,int) ; 
 int Rand32 () ; 

void CreateDummyValue(PACK *p)
{
	UINT size;
	UCHAR *buf;
	// Validate arguments
	if (p == NULL)
	{
		return;
	}

	size = Rand32() % HTTP_PACK_RAND_SIZE_MAX;
	buf = Malloc(size);
	Rand(buf, size);

	PackAddData(p, "pencore", buf, size);

	Free(buf);
}