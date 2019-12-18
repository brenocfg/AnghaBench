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

/* Variables and functions */
 int /*<<< orphan*/  br_rsa_i32_oaep_decrypt ; 
 int /*<<< orphan*/  br_rsa_i32_oaep_encrypt ; 
 int /*<<< orphan*/  br_rsa_i32_pkcs1_sign ; 
 int /*<<< orphan*/  br_rsa_i32_pkcs1_vrfy ; 
 int /*<<< orphan*/  br_rsa_i32_private ; 
 int /*<<< orphan*/  br_rsa_i32_pss_sign ; 
 int /*<<< orphan*/  br_rsa_i32_pss_vrfy ; 
 int /*<<< orphan*/  br_rsa_i32_public ; 
 int /*<<< orphan*/  test_RSA_OAEP (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_RSA_PSS (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_RSA_core (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_RSA_sign (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_RSA_i32(void)
{
	test_RSA_core("RSA i32 core", &br_rsa_i32_public, &br_rsa_i32_private);
	test_RSA_sign("RSA i32 sign", &br_rsa_i32_private,
		&br_rsa_i32_pkcs1_sign, &br_rsa_i32_pkcs1_vrfy);
	test_RSA_OAEP("RSA i32 OAEP",
		&br_rsa_i32_oaep_encrypt, &br_rsa_i32_oaep_decrypt);
	test_RSA_PSS("RSA i32 PSS",
		&br_rsa_i32_pss_sign, &br_rsa_i32_pss_vrfy);
}