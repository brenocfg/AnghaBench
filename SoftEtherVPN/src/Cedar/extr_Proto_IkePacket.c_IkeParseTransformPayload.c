#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h ;
struct TYPE_6__ {int /*<<< orphan*/  ValueList; int /*<<< orphan*/  TransformId; int /*<<< orphan*/  Number; } ;
struct TYPE_5__ {int /*<<< orphan*/  TransformId; int /*<<< orphan*/  Number; } ;
typedef  TYPE_1__ IKE_TRANSFORM_HEADER ;
typedef  TYPE_2__ IKE_PACKET_TRANSFORM_PAYLOAD ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  IkeParseTransformValueList (int /*<<< orphan*/ *) ; 
 int ReadBuf (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

bool IkeParseTransformPayload(IKE_PACKET_TRANSFORM_PAYLOAD *t, BUF *b)
{
	IKE_TRANSFORM_HEADER h;
	// Validate arguments
	if (t == NULL || b == NULL)
	{
		return false;
	}

	if (ReadBuf(b, &h, sizeof(h)) != sizeof(h))
	{
		return false;
	}

	t->Number = h.Number;
	t->TransformId = h.TransformId;
	t->ValueList = IkeParseTransformValueList(b);

	return true;
}