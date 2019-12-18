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
struct crypto_template {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __crypto_lookup_template (char const*) ; 
 struct crypto_template* try_then_request_module (int /*<<< orphan*/ ,char const*) ; 

struct crypto_template *crypto_lookup_template(const char *name)
{
	return try_then_request_module(__crypto_lookup_template(name), name);
}