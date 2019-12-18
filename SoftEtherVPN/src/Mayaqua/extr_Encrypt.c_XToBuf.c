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
typedef  int /*<<< orphan*/  X ;
typedef  int /*<<< orphan*/  BUF ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/ * BioToBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * XToBio (int /*<<< orphan*/ *,int) ; 

BUF *XToBuf(X *x, bool text)
{
	BIO *bio;
	BUF *b;
	// Validate arguments
	if (x == NULL)
	{
		return NULL;
	}

	bio = XToBio(x, text);
	if (bio == NULL)
	{
		return NULL;
	}

	b = BioToBuf(bio);
	FreeBio(bio);

	SeekBuf(b, 0, 0);

	return b;
}