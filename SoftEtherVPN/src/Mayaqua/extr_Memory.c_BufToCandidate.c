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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int /*<<< orphan*/ * Str; int /*<<< orphan*/  LastSelectedTime; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ CANDIDATE ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewCandidateList () ; 
 scalar_t__ ReadBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ReadBufInt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReadBufInt64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Sort (int /*<<< orphan*/ *) ; 
 void* ZeroMalloc (int) ; 

LIST *BufToCandidate(BUF *b)
{
	LIST *o;
	UINT i;
	UINT num;
	// Validate arguments
	if (b == NULL)
	{
		return NULL;
	}

	num = ReadBufInt(b);
	o = NewCandidateList();

	for (i = 0;i < num;i++)
	{
		CANDIDATE *c;
		wchar_t *s;
		UINT64 sec64;
		UINT len, size;
		sec64 = ReadBufInt64(b);
		len = ReadBufInt(b);
		if (len >= 65536)
		{
			break;
		}
		size = (len + 1) * 2;
		s = ZeroMalloc(size);
		if (ReadBuf(b, s, size) != size)
		{
			Free(s);
			break;
		}
		else
		{
			c = ZeroMalloc(sizeof(CANDIDATE));
			c->LastSelectedTime = sec64;
			c->Str = s;
			Add(o, c);
		}
	}

	Sort(o);
	return o;
}