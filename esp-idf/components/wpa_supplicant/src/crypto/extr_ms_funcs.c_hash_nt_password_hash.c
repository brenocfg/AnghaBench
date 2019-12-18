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

/* Variables and functions */
 int md4_vector (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 

int hash_nt_password_hash(const u8 *password_hash, u8 *password_hash_hash)
{
	size_t len = 16;
	return md4_vector(1, &password_hash, &len, password_hash_hash);
}