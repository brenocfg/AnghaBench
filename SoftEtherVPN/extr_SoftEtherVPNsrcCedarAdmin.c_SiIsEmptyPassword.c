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
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */
 scalar_t__ Cmp (void*,int /*<<< orphan*/ *,int) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha0 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

bool SiIsEmptyPassword(void *hash_password)
{
	UCHAR hash[SHA1_SIZE];
	// Validate arguments
	if (hash_password == NULL)
	{
		return false;
	}

	Sha0(hash, "", 0);

	if (Cmp(hash_password, hash, SHA1_SIZE) == 0)
	{
		return true;
	}

	return false;
}