#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int /*<<< orphan*/  tfm; } ;
struct TYPE_4__ {TYPE_1__ essiv; } ;
struct crypt_config {TYPE_2__ iv_gen_private; int /*<<< orphan*/  iv_size; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_cipher_encrypt_one (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crypt_iv_essiv_gen(struct crypt_config *cc, u8 *iv, sector_t sector)
{
	memset(iv, 0, cc->iv_size);
	*(u64 *)iv = cpu_to_le64(sector);
	crypto_cipher_encrypt_one(cc->iv_gen_private.essiv.tfm, iv, iv);
	return 0;
}