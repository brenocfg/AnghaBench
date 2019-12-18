#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int /*<<< orphan*/ * AckReplyList; } ;
typedef  TYPE_1__ OPENVPN_CHANNEL ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  Free (scalar_t__*) ; 
 scalar_t__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 scalar_t__ MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENVPN_MAX_NUMACK ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 

UINT OvsGetAckReplyList(OPENVPN_CHANNEL *c, UINT *ret)
{
	UINT i;
	LIST *o = NULL;
	UINT num;
	// Validate arguments
	if (c == NULL || ret == NULL)
	{
		return 0;
	}

	num = MIN(LIST_NUM(c->AckReplyList), OPENVPN_MAX_NUMACK);

	for (i = 0;i < num;i++)
	{
		UINT *v = LIST_DATA(c->AckReplyList, i);

		if (o == NULL)
		{
			o = NewListFast(NULL);
		}

		Add(o, v);

		ret[i] = *v;
	}

	for (i = 0;i < LIST_NUM(o);i++)
	{
		UINT *v = LIST_DATA(o, i);

		Delete(c->AckReplyList, v);

		Free(v);
	}

	ReleaseList(o);

	return num;
}