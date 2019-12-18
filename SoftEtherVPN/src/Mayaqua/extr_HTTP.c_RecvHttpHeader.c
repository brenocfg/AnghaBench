#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  Version; } ;
struct TYPE_9__ {int NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  TYPE_2__ HTTP_HEADER ;

/* Variables and functions */
 int AddHttpValueStr (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  FreeHttpHeader (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeSafe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 int /*<<< orphan*/  HTTP_HEADER_LINE_MAX_SIZE ; 
 scalar_t__ IsEmptyStr (char*) ; 
 TYPE_2__* NewHttpHeader (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTR_TO_PTR (char*) ; 
 TYPE_1__* ParseToken (char*,char*) ; 
 char* RecvLine (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 

HTTP_HEADER *RecvHttpHeader(SOCK *s)
{
	TOKEN_LIST *token = NULL;
	char *str = NULL;
	HTTP_HEADER *header = NULL;
	// Validate arguments
	if (s == NULL)
	{
		return NULL;
	}

	// Get the first line
	str = RecvLine(s, HTTP_HEADER_LINE_MAX_SIZE);
	if (str == NULL)
	{
		return NULL;
	}

	// Split into tokens
	token = ParseToken(str, " ");

	FreeSafe(PTR_TO_PTR(str));

	if (token->NumTokens < 3)
	{
		FreeToken(token);
		return NULL;
	}

	// Creating a header object
	header = NewHttpHeader(token->Token[0], token->Token[1], token->Token[2]);
	FreeToken(token);

	if (StrCmpi(header->Version, "HTTP/0.9") == 0)
	{
		// The header ends with this line
		return header;
	}

	// Get the subsequent lines
	while (true)
	{
		str = RecvLine(s, HTTP_HEADER_LINE_MAX_SIZE);
		Trim(str);
		if (IsEmptyStr(str))
		{
			// End of header
			FreeSafe(PTR_TO_PTR(str));
			break;
		}

		if (AddHttpValueStr(header, str) == false)
		{
			FreeSafe(PTR_TO_PTR(str));
			FreeHttpHeader(header);
			header = NULL;
			break;
		}

		FreeSafe(PTR_TO_PTR(str));
	}

	return header;
}