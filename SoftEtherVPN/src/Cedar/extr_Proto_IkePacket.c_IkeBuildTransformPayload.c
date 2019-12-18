#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h ;
struct TYPE_7__ {int /*<<< orphan*/  ValueList; int /*<<< orphan*/  TransformId; int /*<<< orphan*/  Number; } ;
struct TYPE_6__ {int /*<<< orphan*/  TransformId; int /*<<< orphan*/  Number; } ;
typedef  TYPE_1__ IKE_TRANSFORM_HEADER ;
typedef  TYPE_2__ IKE_PACKET_TRANSFORM_PAYLOAD ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IkeBuildTransformValueList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  WriteBufBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

BUF *IkeBuildTransformPayload(IKE_PACKET_TRANSFORM_PAYLOAD *t)
{
	IKE_TRANSFORM_HEADER h;
	BUF *ret, *b;
	// Validate arguments
	if (t == NULL)
	{
		return NULL;
	}

	Zero(&h, sizeof(h));
	h.Number = t->Number;
	h.TransformId = t->TransformId;

	ret = NewBuf();
	WriteBuf(ret, &h, sizeof(h));

	b = IkeBuildTransformValueList(t->ValueList);
	WriteBufBuf(ret, b);

	FreeBuf(b);

	return ret;
}