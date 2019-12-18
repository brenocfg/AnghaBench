#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* dthb_chain; struct TYPE_5__* dthb_next; } ;
typedef  TYPE_1__ dtrace_hashbucket_t ;
struct TYPE_6__ {int dth_mask; TYPE_1__** dth_tab; } ;
typedef  TYPE_2__ dtrace_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACE_GETSTR (TYPE_2__*,void*) ; 
 int dtrace_hash_str (char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
dtrace_hash_lookup_string(dtrace_hash_t *hash, const char *str)
{
	int hashval = dtrace_hash_str(str);
	int ndx = hashval & hash->dth_mask;
	dtrace_hashbucket_t *bucket = hash->dth_tab[ndx];

	for (; bucket != NULL; bucket = bucket->dthb_next) {
		if (strcmp(str, DTRACE_GETSTR(hash, bucket->dthb_chain)) == 0)
			return (bucket->dthb_chain);
	}

	return (NULL);
}