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
struct aes_ctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ ALIGN (unsigned long,unsigned long) ; 
 unsigned long PADLOCK_ALIGNMENT ; 
 unsigned long crypto_tfm_ctx_alignment () ; 

__attribute__((used)) static inline struct aes_ctx *aes_ctx_common(void *ctx)
{
	unsigned long addr = (unsigned long)ctx;
	unsigned long align = PADLOCK_ALIGNMENT;

	if (align <= crypto_tfm_ctx_alignment())
		align = 1;
	return (struct aes_ctx *)ALIGN(addr, align);
}