#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
typedef  int UCHAR ;
struct TYPE_4__ {size_t NumTokens; int** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 TYPE_1__* ParseToken (char*,char*) ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ StrLen (int*) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,int*,int) ; 

BUF *BuildDnsHostName(char *hostname)
{
	UINT i;
	UCHAR size;
	TOKEN_LIST *token;
	BUF *b;
	// Validate arguments
	if (hostname == NULL)
	{
		return NULL;
	}

	// Split the host name into tokens
	token = ParseToken(hostname, ".");
	if (token == NULL)
	{
		return NULL;
	}

	b = NewBuf();

	// Add a host string
	for (i = 0;i < token->NumTokens;i++)
	{
		size = (UCHAR)StrLen(token->Token[i]);
		WriteBuf(b, &size, 1);
		WriteBuf(b, token->Token[i], size);
	}

	// NULL character
	size = 0;
	WriteBuf(b, &size, 1);

	SeekBuf(b, 0, 0);

	FreeToken(token);

	return b;
}