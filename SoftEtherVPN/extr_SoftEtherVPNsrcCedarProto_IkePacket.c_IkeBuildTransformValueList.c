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
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  IKE_PACKET_TRANSFORM_VALUE ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IkeBuildTransformValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  WriteBufBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BUF *IkeBuildTransformValueList(LIST *o)
{
	BUF *b;
	UINT i;
	// Validate arguments
	if (o == NULL)
	{
		return NULL;
	}

	b = NewBuf();

	for (i = 0;i < LIST_NUM(o);i++)
	{
		IKE_PACKET_TRANSFORM_VALUE *v = LIST_DATA(o, i);
		BUF *tmp = IkeBuildTransformValue(v);

		WriteBufBuf(b, tmp);

		FreeBuf(tmp);
	}

	return b;
}