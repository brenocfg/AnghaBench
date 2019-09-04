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
typedef  int /*<<< orphan*/  K ;
typedef  int /*<<< orphan*/  BUF ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/ * BioToK (int /*<<< orphan*/ *,int,int,char*) ; 
 int /*<<< orphan*/ * BufToBio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBio (int /*<<< orphan*/ *) ; 

K *BufToK(BUF *b, bool private_key, bool text, char *password)
{
	BIO *bio;
	K *k;
	// Validate arguments
	if (b == NULL)
	{
		return NULL;
	}

	bio = BufToBio(b);
	k = BioToK(bio, private_key, text, password);
	FreeBio(bio);

	return k;
}