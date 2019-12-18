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
typedef  int /*<<< orphan*/  size ;
typedef  int /*<<< orphan*/  hash ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_3__ {int Size; int /*<<< orphan*/ * Buf; } ;
typedef  int /*<<< orphan*/  IO ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Endian32 (int) ; 
 int FileWrite (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int MD5_SIZE ; 
 int /*<<< orphan*/  Md5 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

bool BufToFile(IO *o, BUF *b)
{
	UCHAR hash[MD5_SIZE];
	UINT size;

	// Validate arguments
	if (o == NULL || b == NULL)
	{
		return false;
	}

	// Hash the data
	Md5(hash, b->Buf, b->Size);

	size = Endian32(b->Size);

	// Write the size
	if (FileWrite(o, &size, sizeof(size)) == false)
	{
		return false;
	}

	// Write a hash
	if (FileWrite(o, hash, sizeof(hash)) == false)
	{
		return false;
	}

	// Write the data
	if (FileWrite(o, b->Buf, b->Size) == false)
	{
		return false;
	}

	return true;
}