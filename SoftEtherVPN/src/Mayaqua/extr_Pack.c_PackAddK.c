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
typedef  int /*<<< orphan*/  K ;
typedef  int /*<<< orphan*/  ELEMENT ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * KToBuf (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PackAddBuf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

ELEMENT *PackAddK(PACK *p, char *name, K *k)
{
	BUF *b;
	ELEMENT *e = NULL;
	// Validate arguments
	if (p == NULL || name == NULL || k == NULL)
	{
		return NULL;
	}

	b = KToBuf(k, false, NULL);
	if (b == NULL)
	{
		return NULL;
	}

	e = PackAddBuf(p, name, b);
	FreeBuf(b);

	return e;
}