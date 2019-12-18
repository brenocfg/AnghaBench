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
typedef  int /*<<< orphan*/  u32 ;
struct rtattr {int dummy; } ;
struct crypto_type {int dummy; } ;
struct crypto_alg {int dummy; } ;

/* Variables and functions */
 struct crypto_alg* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (char const*) ; 
 int PTR_ERR (char const*) ; 
 char* crypto_attr_alg_name (struct rtattr*) ; 
 struct crypto_alg* crypto_find_alg (char const*,struct crypto_type const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct crypto_alg *crypto_attr_alg2(struct rtattr *rta,
				    const struct crypto_type *frontend,
				    u32 type, u32 mask)
{
	const char *name;
	int err;

	name = crypto_attr_alg_name(rta);
	err = PTR_ERR(name);
	if (IS_ERR(name))
		return ERR_PTR(err);

	return crypto_find_alg(name, frontend, type, mask);
}