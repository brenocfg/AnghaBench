#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
typedef  int UCHAR ;
struct TYPE_12__ {int /*<<< orphan*/  Size; scalar_t__ Buf; } ;
struct TYPE_11__ {int Code; int Id; int* Data; int DataSize; int /*<<< orphan*/  OptionList; } ;
struct TYPE_10__ {int DataSize; int Type; int* Data; } ;
typedef  TYPE_1__ PPP_OPTION ;
typedef  TYPE_2__ PPP_LCP ;
typedef  TYPE_3__ BUF ;

/* Variables and functions */
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 TYPE_3__* NewBuf () ; 
 int /*<<< orphan*/  SeekBuf (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_USHORT (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_3__*,int*,int) ; 

BUF *BuildLCPData(PPP_LCP *c)
{
	BUF *b;
	UCHAR zero = 0;
	UINT i;
	// Validate arguments
	if (c == NULL)
	{
		return NULL;
	}

	b = NewBuf();

	// Code
	WriteBuf(b, &c->Code, 1);

	// ID
	WriteBuf(b, &c->Id, 1);

	// Length (to be updated later)
	zero = 0;
	WriteBuf(b, &zero, 1);
	WriteBuf(b, &zero, 1);

	if (c->Data == NULL)
	{
		// Option List
		for (i = 0;i < LIST_NUM(c->OptionList);i++)
		{
			PPP_OPTION *o = LIST_DATA(c->OptionList, i);
			UCHAR sz = o->DataSize + 2;

			WriteBuf(b, &o->Type, 1);
			WriteBuf(b, &sz, 1);

			WriteBuf(b, o->Data, o->DataSize);
		}
	}
	else
	{
		// Data
		WriteBuf(b, c->Data, c->DataSize);
	}

	SeekBuf(b, 0, 0);

	// Update Length
	WRITE_USHORT(((UCHAR *)b->Buf) + 2, b->Size);

	return b;
}