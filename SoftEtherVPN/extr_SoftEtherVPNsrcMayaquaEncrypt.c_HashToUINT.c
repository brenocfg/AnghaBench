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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Endian32 (int /*<<< orphan*/ ) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha1 (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 

UINT HashToUINT(void *data, UINT size)
{
	UCHAR hash[SHA1_SIZE];
	UINT u;
	// Validate arguments
	if (data == NULL && size != 0)
	{
		return 0;
	}

	Sha1(hash, data, size);

	Copy(&u, hash, sizeof(UINT));

	u = Endian32(u);

	return u;
}