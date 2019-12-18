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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 size_t AES_PRIV_NR_POS ; 
 int /*<<< orphan*/  rijndaelEncrypt (void*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

void  aes_encrypt(void *ctx, const u8 *plain, u8 *crypt)
{
	u32 *rk = ctx;
	rijndaelEncrypt(ctx, rk[AES_PRIV_NR_POS], plain, crypt);
}