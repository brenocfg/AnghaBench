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
typedef  int /*<<< orphan*/  username2 ;
typedef  int /*<<< orphan*/  domainname2 ;
typedef  char UCHAR ;
struct TYPE_5__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (char*,char*,int) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 int IsEmptyStr (char*) ; 
 int MAX_SIZE ; 
 TYPE_1__* NewBuf () ; 
 int /*<<< orphan*/  ParseNtUsername (char*,char*,int,char*,int,int) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha1 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int StrLen (char*) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_1__*,char*,int) ; 

void MsChapV2_GenerateChallenge8(UCHAR *dst, UCHAR *client_challenge, UCHAR *server_challenge, char *username)
{
	BUF *b;
	UCHAR hash[SHA1_SIZE];
	char username2[MAX_SIZE];
	char domainname2[MAX_SIZE];
	// Validate arguments
	if (dst == NULL || client_challenge == NULL || server_challenge == NULL)
	{
		return;
	}

	b = NewBuf();

	WriteBuf(b, client_challenge, 16);
	WriteBuf(b, server_challenge, 16);

	ParseNtUsername(username, username2, sizeof(username2), domainname2, sizeof(domainname2), true);

	if (IsEmptyStr(username2) == false)
	{
		WriteBuf(b, username2, StrLen(username2));
	}

	Sha1(hash, b->Buf, b->Size);

	FreeBuf(b);

	Copy(dst, hash, 8);
}