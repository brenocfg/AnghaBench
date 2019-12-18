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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct md4_ctx {int byte_count; int* block; int* hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32_array (int*,int) ; 
 int /*<<< orphan*/  le32_to_cpu_array (int*,int) ; 
 int /*<<< orphan*/  md4_transform (int*,int*) ; 
 int /*<<< orphan*/  md4_transform_helper (struct md4_ctx*) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,unsigned int,char*,int,int,int,int) ; 

__attribute__((used)) static void md4_final_ascii(struct md4_ctx *mctx, char *out, unsigned int len)
{
	const unsigned int offset = mctx->byte_count & 0x3f;
	char *p = (char *)mctx->block + offset;
	int padding = 56 - (offset + 1);

	*p++ = 0x80;
	if (padding < 0) {
		memset(p, 0x00, padding + sizeof (uint64_t));
		md4_transform_helper(mctx);
		p = (char *)mctx->block;
		padding = 56;
	}

	memset(p, 0, padding);
	mctx->block[14] = mctx->byte_count << 3;
	mctx->block[15] = mctx->byte_count >> 29;
	le32_to_cpu_array(mctx->block, (sizeof(mctx->block) -
	                  sizeof(uint64_t)) / sizeof(uint32_t));
	md4_transform(mctx->hash, mctx->block);
	cpu_to_le32_array(mctx->hash, sizeof(mctx->hash) / sizeof(uint32_t));

	snprintf(out, len, "%08X%08X%08X%08X",
		 mctx->hash[0], mctx->hash[1], mctx->hash[2], mctx->hash[3]);
}