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
typedef  int /*<<< orphan*/  key_serial_t ;
typedef  int /*<<< orphan*/  key_ref_t ;
struct TYPE_2__ {long serial; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 unsigned long KEY_LOOKUP_CREATE ; 
 int /*<<< orphan*/  KEY_SEARCH ; 
 long PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_ref_put (int /*<<< orphan*/ ) ; 
 TYPE_1__* key_ref_to_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_user_key (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

long keyctl_get_keyring_ID(key_serial_t id, int create)
{
	key_ref_t key_ref;
	unsigned long lflags;
	long ret;

	lflags = create ? KEY_LOOKUP_CREATE : 0;
	key_ref = lookup_user_key(id, lflags, KEY_SEARCH);
	if (IS_ERR(key_ref)) {
		ret = PTR_ERR(key_ref);
		goto error;
	}

	ret = key_ref_to_ptr(key_ref)->serial;
	key_ref_put(key_ref);
error:
	return ret;
}