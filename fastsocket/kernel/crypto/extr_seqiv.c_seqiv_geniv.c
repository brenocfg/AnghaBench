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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct seqiv_ctx {int /*<<< orphan*/  salt; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_xor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void seqiv_geniv(struct seqiv_ctx *ctx, u8 *info, u64 seq,
			unsigned int ivsize)
{
	unsigned int len = ivsize;

	if (ivsize > sizeof(u64)) {
		memset(info, 0, ivsize - sizeof(u64));
		len = sizeof(u64);
	}
	seq = cpu_to_be64(seq);
	memcpy(info + ivsize - len, &seq, len);
	crypto_xor(info, ctx->salt, ivsize);
}