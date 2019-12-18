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
typedef  int /*<<< orphan*/  USHORT ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  SSTP_ATTRIBUTE ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Endian16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/ * SstpBuildAttribute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WriteBufBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BUF *SstpBuildAttributeList(LIST *o, USHORT message_type)
{
	UINT i;
	BUF *b;
	USHORT us;
	// Validate arguments
	if (o == NULL)
	{
		return NULL;
	}

	b = NewBuf();

	us = Endian16(message_type);
	WriteBuf(b, &us, sizeof(USHORT));

	us = Endian16((USHORT)LIST_NUM(o));
	WriteBuf(b, &us, sizeof(USHORT));

	for (i = 0;i < LIST_NUM(o);i++)
	{
		SSTP_ATTRIBUTE *a = LIST_DATA(o, i);
		BUF *ab = SstpBuildAttribute(a);

		if (ab != NULL)
		{
			WriteBufBuf(b, ab);

			FreeBuf(ab);
		}
	}

	return b;
}