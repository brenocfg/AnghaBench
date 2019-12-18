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
struct TYPE_2__ {char value; char* data; } ;
struct key {size_t datalen; TYPE_1__ payload; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,size_t) ; 

__attribute__((used)) static int
cifs_idmap_key_instantiate(struct key *key, const void *data, size_t datalen)
{
	char *payload;

	/*
	 * If the payload is less than or equal to the size of a pointer, then
	 * an allocation here is wasteful. Just copy the data directly to the
	 * payload.value union member instead.
	 *
	 * With this however, you must check the datalen before trying to
	 * dereference payload.data!
	 */
	if (datalen <= sizeof(key->payload)) {
		key->payload.value = 0;
		memcpy(&key->payload.value, data, datalen);
		key->datalen = datalen;
		return 0;
	}
	payload = kmalloc(datalen, GFP_KERNEL);
	if (!payload)
		return -ENOMEM;

	memcpy(payload, data, datalen);
	key->payload.data = payload;
	key->datalen = datalen;
	return 0;
}