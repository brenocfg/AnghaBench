#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct key_type {int /*<<< orphan*/  match; } ;
typedef  int /*<<< orphan*/  key_ref_t ;
struct TYPE_2__ {int /*<<< orphan*/  cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOKEY ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  keyring_search_aux (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct key_type*,char const*,int /*<<< orphan*/ ,int) ; 

key_ref_t keyring_search(key_ref_t keyring,
			 struct key_type *type,
			 const char *description)
{
	if (!type->match)
		return ERR_PTR(-ENOKEY);

	return keyring_search_aux(keyring, current->cred,
				  type, description, type->match, false);
}