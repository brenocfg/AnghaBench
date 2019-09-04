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
typedef  int /*<<< orphan*/  P12 ;
typedef  int /*<<< orphan*/  BUF ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/ * BioToBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * P12ToBio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BUF *P12ToBuf(P12 *p12)
{
	BIO *bio;
	BUF *buf;
	// Validate arguments
	if (p12 == NULL)
	{
		return NULL;
	}

	bio = P12ToBio(p12);
	if (bio == NULL)
	{
		return NULL;
	}

	buf = BioToBuf(bio);
	FreeBio(bio);

	SeekBuf(buf, 0, 0);

	return buf;
}