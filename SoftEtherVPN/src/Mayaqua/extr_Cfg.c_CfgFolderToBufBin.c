#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hash ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_6__ {int Size; scalar_t__ Buf; } ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  CfgOutputFolderBin (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* NewBuf () ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha0 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * TAG_BINARY ; 
 int /*<<< orphan*/  WriteBuf (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

BUF *CfgFolderToBufBin(FOLDER *f)
{
	BUF *b;
	UCHAR hash[SHA1_SIZE];
	// Validate arguments
	if (f == NULL)
	{
		return NULL;
	}

	b = NewBuf();

	// Header
	WriteBuf(b, TAG_BINARY, 8);

	// Hash area
	Zero(hash, sizeof(hash));
	WriteBuf(b, hash, sizeof(hash));

	// Output the root folder (recursive)
	CfgOutputFolderBin(b, f);

	// Hash
	Sha0(((UCHAR *)b->Buf) + 8, ((UCHAR *)b->Buf) + 8 + SHA1_SIZE, b->Size - 8 - SHA1_SIZE);

	return b;
}