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
typedef  int /*<<< orphan*/  aes_rval ;
typedef  int /*<<< orphan*/  aes_encrypt_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  aes_encrypt_cbc (unsigned char const*,int /*<<< orphan*/ *,int,unsigned char*,int /*<<< orphan*/ *) ; 

aes_rval aes_encrypt(const unsigned char *in_blk, unsigned char *out_blk, aes_encrypt_ctx cx[1])
{
       return aes_encrypt_cbc(in_blk, NULL, 1, out_blk, cx);    
}