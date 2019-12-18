#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* buckets; } ;
typedef  TYPE_1__ HT ;

/* Variables and functions */
 int /*<<< orphan*/  HT_clear (TYPE_1__*,void (*) (void*)) ; 
 int /*<<< orphan*/  xfree (TYPE_1__*) ; 

__attribute__((used)) static void
HT_free(HT *ht, void (*free_value)(void *value))
{
	HT_clear(ht, free_value);
	xfree(ht->buckets);
	xfree(ht);
}