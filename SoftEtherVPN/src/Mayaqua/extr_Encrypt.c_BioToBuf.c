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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  BUF ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 scalar_t__ BIO_number_written (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_read (int /*<<< orphan*/ *,void*,scalar_t__) ; 
 int /*<<< orphan*/  BIO_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (void*) ; 
 void* Malloc (scalar_t__) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,void*,scalar_t__) ; 

BUF *BioToBuf(BIO *bio)
{
	BUF *b;
	UINT size;
	void *tmp;
	// Validate arguments
	if (bio == NULL)
	{
		return NULL;
	}

	BIO_seek(bio, 0);
	size = (UINT)BIO_number_written(bio);
	tmp = Malloc(size);
	BIO_read(bio, tmp, size);

	b = NewBuf();
	WriteBuf(b, tmp, size);
	Free(tmp);

	return b;
}