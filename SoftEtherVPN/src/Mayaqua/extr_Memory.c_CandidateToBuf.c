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
struct TYPE_3__ {int /*<<< orphan*/  Str; int /*<<< orphan*/  LastSelectedTime; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ CANDIDATE ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ UniStrLen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniStrSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBufInt (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  WriteBufInt64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BUF *CandidateToBuf(LIST *o)
{
	BUF *b;
	UINT i;
	// Validate arguments
	if (o == NULL)
	{
		return NULL;
	}

	b = NewBuf();
	WriteBufInt(b, LIST_NUM(o));
	for (i = 0;i < LIST_NUM(o);i++)
	{
		CANDIDATE *c = LIST_DATA(o, i);
		WriteBufInt64(b, c->LastSelectedTime);
		WriteBufInt(b, UniStrLen(c->Str));
		WriteBuf(b, c->Str, UniStrSize(c->Str));
	}

	SeekBuf(b, 0, 0);

	return b;
}