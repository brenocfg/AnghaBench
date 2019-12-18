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
typedef  int /*<<< orphan*/  digest ;
typedef  char UCHAR ;
struct TYPE_5__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 TYPE_1__* NewBuf () ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha1 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int StrLen (char*) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_1__*,char*,int) ; 

void MsChapV2Server_GenerateResponse(UCHAR *dst, UCHAR *nt_password_hash_hash, UCHAR *client_response, UCHAR *challenge8)
{
	UCHAR digest[SHA1_SIZE];
	BUF *b;
	char *magic1 = "Magic server to client signing constant";
	char *magic2 = "Pad to make it do more than one iteration";
	// Validate arguments
	if (dst == NULL || nt_password_hash_hash == NULL || client_response == NULL || challenge8 == NULL)
	{
		return;
	}

	b = NewBuf();
	WriteBuf(b, nt_password_hash_hash, 16);
	WriteBuf(b, client_response, 24);
	WriteBuf(b, magic1, StrLen(magic1));
	Sha1(digest, b->Buf, b->Size);
	FreeBuf(b);

	b = NewBuf();
	WriteBuf(b, digest, sizeof(digest));
	WriteBuf(b, challenge8, 8);
	WriteBuf(b, magic2, StrLen(magic2));
	Sha1(dst, b->Buf, b->Size);
	FreeBuf(b);
}