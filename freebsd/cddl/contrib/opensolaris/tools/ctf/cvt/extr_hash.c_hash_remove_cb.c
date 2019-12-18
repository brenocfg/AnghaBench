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
struct TYPE_2__ {int (* h_cmp ) (void*,void*) ;} ;
typedef  TYPE_1__ hash_t ;

/* Variables and functions */
 int stub1 (void*,void*) ; 

__attribute__((used)) static int
hash_remove_cb(void *key1, void *key2, void *arg)
{
	hash_t *hash = arg;
	return (hash->h_cmp(key1, key2));
}