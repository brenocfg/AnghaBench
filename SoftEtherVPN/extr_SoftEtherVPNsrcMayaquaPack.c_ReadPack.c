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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  ELEMENT ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int AddElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ MAX_ELEMENT_NUM ; 
 scalar_t__ ReadBufInt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ReadElement (int /*<<< orphan*/ *) ; 

bool ReadPack(BUF *b, PACK *p)
{
	UINT i, num;
	// Validate arguments
	if (b == NULL || p == NULL)
	{
		return false;
	}

	// The number of ELEMENTs
	num = ReadBufInt(b);
	if (num > MAX_ELEMENT_NUM)
	{
		// Number exceeds
		return false;
	}

	// Read the ELEMENT
	for (i = 0;i < num;i++)
	{
		ELEMENT *e;
		e = ReadElement(b);
		if (AddElement(p, e) == false)
		{
			// Adding error
			return false;
		}
	}

	return true;
}