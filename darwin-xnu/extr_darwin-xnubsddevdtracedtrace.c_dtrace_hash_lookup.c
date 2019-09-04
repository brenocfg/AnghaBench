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
typedef  int /*<<< orphan*/  dtrace_probe_t ;
typedef  int /*<<< orphan*/  dtrace_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACE_GETSTR (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/ * dtrace_hash_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dtrace_probe_t *
dtrace_hash_lookup(dtrace_hash_t *hash, void *template)
{
	return dtrace_hash_lookup_string(hash, DTRACE_GETSTR(hash, template));
}