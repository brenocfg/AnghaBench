#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  c ;
typedef  scalar_t__ UINT ;
typedef  char UCHAR ;
struct TYPE_9__ {scalar_t__ Size; scalar_t__ Buf; } ;
struct TYPE_8__ {int /*<<< orphan*/  SecureMode; } ;
typedef  TYPE_1__ SOCK ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 char* Malloc (int) ; 
 TYPE_2__* NewBuf () ; 
 int RecvAll (TYPE_1__*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_2__*,char*,int) ; 

char *RecvLine(SOCK *s, UINT max_size)
{
	BUF *b;
	char c;
	char *str;
	// Validate arguments
	if (s == NULL || max_size == 0)
	{
		return NULL;
	}

	b = NewBuf();
	while (true)
	{
		UCHAR *buf;
		if (RecvAll(s, &c, sizeof(c), s->SecureMode) == false)
		{
			FreeBuf(b);
			return NULL;
		}
		WriteBuf(b, &c, sizeof(c));
		buf = (UCHAR *)b->Buf;
		if (b->Size > max_size)
		{
			FreeBuf(b);
			return NULL;
		}
		if (b->Size >= 1)
		{
			if (buf[b->Size - 1] == '\n')
			{
				b->Size--;
				if (b->Size >= 1)
				{
					if (buf[b->Size - 1] == '\r')
					{
						b->Size--;
					}
				}
				str = Malloc(b->Size + 1);
				Copy(str, b->Buf, b->Size);
				str[b->Size] = 0;
				FreeBuf(b);

				return str;
			}
		}
	}
}