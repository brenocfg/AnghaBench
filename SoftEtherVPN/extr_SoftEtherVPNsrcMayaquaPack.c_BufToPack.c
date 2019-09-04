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
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int ReadPack (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

PACK *BufToPack(BUF *b)
{
	PACK *p;
	// Validate arguments
	if (b == NULL)
	{
		return NULL;
	}

	p = NewPack();
	if (ReadPack(b, p) == false)
	{
		FreePack(p);
		return NULL;
	}

	return p;
}