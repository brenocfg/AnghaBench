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
 int /*<<< orphan*/ * BioToP12 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BufToBio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBio (int /*<<< orphan*/ *) ; 

P12 *BufToP12(BUF *b)
{
	P12 *p12;
	BIO *bio;
	// Validate arguments
	if (b == NULL)
	{
		return NULL;
	}

	bio = BufToBio(b);
	if (bio == NULL)
	{
		return NULL;
	}

	p12 = BioToP12(bio);
	FreeBio(bio);

	return p12;
}