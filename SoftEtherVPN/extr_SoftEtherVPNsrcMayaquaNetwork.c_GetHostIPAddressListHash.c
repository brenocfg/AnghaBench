#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_5__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Endian64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeHostIPAddressList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetHostIPAddressList () ; 
 int /*<<< orphan*/  IPToStr (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 TYPE_1__* NewBuf () ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBufStr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  Zero (char*,int) ; 

UINT64 GetHostIPAddressListHash()
{
	UINT i;
	LIST *o;
	BUF *buf = NewBuf();
	UCHAR hash[SHA1_SIZE];
	UINT64 ret = 0;

	o = GetHostIPAddressList();

	if (o != NULL)
	{
		for (i = 0;i < LIST_NUM(o);i++)
		{
			IP *ip = LIST_DATA(o, i);
			char tmp[128];

			Zero(tmp, sizeof(tmp));
			IPToStr(tmp, sizeof(tmp), ip);

			WriteBufStr(buf, tmp);
		}

		FreeHostIPAddressList(o);
	}

	WriteBufStr(buf, "test");

	Sha1(hash, buf->Buf, buf->Size);

	FreeBuf(buf);

	Copy(&ret, hash, sizeof(UINT64));

	ret = Endian64(ret);

	return ret;
}