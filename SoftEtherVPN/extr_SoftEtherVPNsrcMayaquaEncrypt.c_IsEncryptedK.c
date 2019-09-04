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

/* Variables and functions */
 int /*<<< orphan*/ * BufToK (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeK (int /*<<< orphan*/ *) ; 
 int IsBase64 (int /*<<< orphan*/ *) ; 

bool IsEncryptedK(BUF *b, bool private_key)
{
	K *k;
	// Validate arguments
	if (b == NULL)
	{
		return false;
	}
	if (IsBase64(b) == false)
	{
		return false;
	}

	k = BufToK(b, private_key, true, NULL);
	if (k != NULL)
	{
		FreeK(k);
		return false;
	}

	return true;
}