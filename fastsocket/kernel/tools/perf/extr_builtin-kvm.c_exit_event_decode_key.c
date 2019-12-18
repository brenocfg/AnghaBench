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
struct perf_kvm_stat {int dummy; } ;
struct event_key {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 char* get_exit_reason (struct perf_kvm_stat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static void exit_event_decode_key(struct perf_kvm_stat *kvm,
				  struct event_key *key,
				  char decode[20])
{
	const char *exit_reason = get_exit_reason(kvm, key->key);

	scnprintf(decode, 20, "%s", exit_reason);
}