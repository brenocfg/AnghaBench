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

/* Variables and functions */
 size_t strlen (char const*) ; 

hash_index_t hash_function_string(const void *key)
{
    hash_index_t hash = 5381;
    const char *name = (const char *)key;
    size_t string_len = strlen(name);
    for (size_t i = 0; i < string_len; ++i) {
        hash = ((hash << 5) + hash ) + name[i];
    }
    return hash;
}