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
struct request_key_auth {TYPE_2__* target_key; } ;
struct TYPE_3__ {struct request_key_auth* data; } ;
struct key {TYPE_1__ payload; } ;
typedef  scalar_t__ key_serial_t ;
struct TYPE_4__ {scalar_t__ serial; } ;

/* Variables and functions */

__attribute__((used)) static int key_get_instantiation_authkey_match(const struct key *key,
					       const void *_id)
{
	struct request_key_auth *rka = key->payload.data;
	key_serial_t id = (key_serial_t)(unsigned long) _id;

	return rka->target_key->serial == id;
}