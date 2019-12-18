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
typedef  int hash_index_t ;
typedef  int /*<<< orphan*/  bt_bdaddr_t ;

/* Variables and functions */

hash_index_t hash_function_bdaddr(const void *key)
{
    hash_index_t hash = 5381;
    const char *bytes = (const char *)key;
    for (size_t i = 0; i < sizeof(bt_bdaddr_t); ++i) {
        hash = ((hash << 5) + hash) + bytes[i];
    }
    return hash;
}