#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  h ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_17__ {char* Method; char* Path; char* Protocol; char* Hostname; char* Referer; char* UserAgent; int /*<<< orphan*/  Port; } ;
struct TYPE_14__ {TYPE_1__* TCPHeader; } ;
struct TYPE_16__ {int PayloadSize; TYPE_2__ L4; int /*<<< orphan*/ * Payload; } ;
struct TYPE_15__ {int NumTokens; char** Token; } ;
struct TYPE_13__ {int /*<<< orphan*/  DstPort; } ;
typedef  TYPE_3__ TOKEN_LIST ;
typedef  TYPE_4__ PKT ;
typedef  TYPE_5__ HTTPLOG ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 char* CfgReadNextLine (int /*<<< orphan*/ *) ; 
 TYPE_5__* Clone (TYPE_5__*,int) ; 
 scalar_t__ CmpCaseIgnore (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  Endian16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeToken (TYPE_3__*) ; 
 int INFINITE ; 
 int IsEmptyStr (char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * NewBuf () ; 
 TYPE_3__* ParseToken (char*,char*) ; 
 int SearchStr (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ StrCmpi (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  StrUpper (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Zero (TYPE_5__*,int) ; 

HTTPLOG *ParseHttpAccessLog(PKT *pkt)
{
	HTTPLOG h;
	UCHAR *buf;
	UINT size;
	BUF *b;
	char *line1;
	bool ok = false;
	// Validate arguments
	if (pkt == NULL)
	{
		return NULL;
	}

	buf = pkt->Payload;
	size = pkt->PayloadSize;

	if (size <= 5)
	{
		return NULL;
	}

	// Check whether it starts with the HTTP-specific string
	if (CmpCaseIgnore(buf, "GET ", 4) != 0 &&
		CmpCaseIgnore(buf, "HEAD ", 5) != 0 &&
		CmpCaseIgnore(buf, "POST ", 5) != 0)
	{
		return NULL;
	}

	Zero(&h, sizeof(h));

	h.Port = Endian16(pkt->L4.TCPHeader->DstPort);

	b = NewBuf();
	WriteBuf(b, buf, size);
	SeekBuf(b, 0, 0);

	line1 = CfgReadNextLine(b);

	if (line1 != NULL)
	{
		TOKEN_LIST *tokens = ParseToken(line1, " \t");
		if (tokens != NULL)
		{
			if (tokens->NumTokens == 3)
			{
				StrCpy(h.Method, sizeof(h.Hostname), tokens->Token[0]);
				Trim(h.Method);

				StrCpy(h.Path, sizeof(h.Path), tokens->Token[1]);
				Trim(h.Path);

				StrCpy(h.Protocol, sizeof(h.Protocol), tokens->Token[2]);
				Trim(h.Protocol);

				StrUpper(h.Method);

				while (true)
				{
					char *line = CfgReadNextLine(b);
					UINT i;

					if (line == NULL)
					{
						break;
					}

					i = SearchStr(line, ":", 0);
					if (i != INFINITE && i < (MAX_SIZE / 2))
					{
						char name[MAX_SIZE];
						char value[MAX_SIZE];

						StrCpy(name, sizeof(name), line);
						name[i] = 0;
						Trim(name);

						StrCpy(value, sizeof(value), line + i + 1);
						Trim(value);

						if (StrCmpi(name, "host") == 0)
						{
							StrCpy(h.Hostname, sizeof(h.Hostname), value);
						}
						else if (StrCmpi(name, "referer") == 0)
						{
							StrCpy(h.Referer, sizeof(h.Referer), value);
						}
						else if (StrCmpi(name, "user-agent") == 0)
						{
							StrCpy(h.UserAgent, sizeof(h.UserAgent), value);
						}
					}

					Free(line);
				}

				if (IsEmptyStr(h.Hostname) == false)
				{
					ok = true;
				}
			}
			FreeToken(tokens);
		}
	}

	Free(line1);
	FreeBuf(b);

	if (ok)
	{
		return Clone(&h, sizeof(h));
	}
	else
	{
		return NULL;
	}
}