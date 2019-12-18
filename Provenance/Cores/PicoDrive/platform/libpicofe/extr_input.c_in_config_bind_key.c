#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* binds; int key_count; char** key_names; int /*<<< orphan*/  drv_id; } ;
typedef  TYPE_1__ in_dev_t ;
struct TYPE_5__ {int (* get_key_code ) (char const*) ;} ;

/* Variables and functions */
 TYPE_3__ DRV (int /*<<< orphan*/ ) ; 
 int IN_BINDTYPE_COUNT ; 
 int IN_BINDTYPE_NONE ; 
 size_t IN_BIND_OFFS (int,int) ; 
 TYPE_1__* get_dev (int) ; 
 int* in_alloc_binds (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lprintf (char*,char const*) ; 
 scalar_t__ strcasecmp (char const*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ strtoul (char const*,char**,int) ; 
 int stub1 (char const*) ; 

int in_config_bind_key(int dev_id, const char *key, int acts, int bind_type)
{
	in_dev_t *dev;
	int i, offs, kc;

	dev = get_dev(dev_id);
	if (dev == NULL || bind_type >= IN_BINDTYPE_COUNT)
		return -1;

	/* maybe a raw code? */
	if (key[0] == '\\' && key[1] == 'x') {
		char *p = NULL;
		kc = (int)strtoul(key + 2, &p, 16);
		if (p == NULL || *p != 0)
			kc = -1;
	}
	else {
		/* device specific key name */
		if (dev->binds == NULL) {
			dev->binds = in_alloc_binds(dev->drv_id, dev->key_count);
			if (dev->binds == NULL)
				return -1;
		}

		kc = -1;
		if (dev->key_names != NULL) {
			for (i = 0; i < dev->key_count; i++) {
				const char *k = dev->key_names[i];
				if (k != NULL && strcasecmp(k, key) == 0) {
					kc = i;
					break;
				}
			}
		}

		if (kc < 0)
			kc = DRV(dev->drv_id).get_key_code(key);
		if (kc < 0 && strlen(key) == 1) {
			/* assume scancode */
			kc = key[0];
		}
	}

	if (kc < 0 || kc >= dev->key_count) {
		lprintf("input: bad key: %s\n", key);
		return -1;
	}

	if (bind_type == IN_BINDTYPE_NONE) {
		for (i = 0; i < IN_BINDTYPE_COUNT; i++)
			dev->binds[IN_BIND_OFFS(kc, i)] = 0;
		return 0;
	}

	offs = IN_BIND_OFFS(kc, bind_type);
	if (dev->binds[offs] == -1)
		dev->binds[offs] = 0;
	dev->binds[offs] |= acts;
	return 0;
}