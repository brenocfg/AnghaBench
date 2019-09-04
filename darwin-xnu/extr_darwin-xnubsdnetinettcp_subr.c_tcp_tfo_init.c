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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 int TCP_FASTOPEN_KEYLEN ; 
 int /*<<< orphan*/  aes_encrypt_key128 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_frandom (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tfo_ctx ; 

__attribute__((used)) static void
tcp_tfo_init(void)
{
	u_char key[TCP_FASTOPEN_KEYLEN];

	read_frandom(key, sizeof(key));
	aes_encrypt_key128(key, &tfo_ctx);
}