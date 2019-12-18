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
typedef  int /*<<< orphan*/  MD4_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD4Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD4Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD4Update (int /*<<< orphan*/ *,unsigned char*,int) ; 

unsigned Com_BlockChecksum (void *buffer, int length)
{
	int			digest[4];
	unsigned	val;
	MD4_CTX		ctx;

	MD4Init (&ctx);
	MD4Update (&ctx, (unsigned char *)buffer, length);
	MD4Final ( (unsigned char *)digest, &ctx);
	
	val = digest[0] ^ digest[1] ^ digest[2] ^ digest[3];

	return val;
}