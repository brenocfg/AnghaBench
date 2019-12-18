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
struct rtattr {int dummy; } ;
struct crypto_instance {int dummy; } ;

/* Variables and functions */
 int CRYPTO_MAX_ALG_NAME ; 
 int ENAMETOOLONG ; 
 struct crypto_instance* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (char const*) ; 
 int PTR_ERR (char const*) ; 
 char* crypto_attr_alg_name (struct rtattr*) ; 
 struct crypto_instance* crypto_gcm_alloc_common (struct rtattr**,char*,char*,char*) ; 
 int snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static struct crypto_instance *crypto_gcm_alloc(struct rtattr **tb)
{
	int err;
	const char *cipher_name;
	char ctr_name[CRYPTO_MAX_ALG_NAME];
	char full_name[CRYPTO_MAX_ALG_NAME];

	cipher_name = crypto_attr_alg_name(tb[1]);
	err = PTR_ERR(cipher_name);
	if (IS_ERR(cipher_name))
		return ERR_PTR(err);

	if (snprintf(ctr_name, CRYPTO_MAX_ALG_NAME, "ctr(%s)", cipher_name) >=
	    CRYPTO_MAX_ALG_NAME)
		return ERR_PTR(-ENAMETOOLONG);

	if (snprintf(full_name, CRYPTO_MAX_ALG_NAME, "gcm(%s)", cipher_name) >=
	    CRYPTO_MAX_ALG_NAME)
		return ERR_PTR(-ENAMETOOLONG);

	return crypto_gcm_alloc_common(tb, full_name, ctr_name, "ghash");
}