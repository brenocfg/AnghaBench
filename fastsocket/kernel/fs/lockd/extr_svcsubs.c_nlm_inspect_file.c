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
struct nlm_host {int dummy; } ;
struct nlm_file {int dummy; } ;
typedef  int /*<<< orphan*/  nlm_host_match_fn_t ;

/* Variables and functions */
 int nlm_traverse_locks (struct nlm_host*,struct nlm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsvc_traverse_blocks (struct nlm_host*,struct nlm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsvc_traverse_shares (struct nlm_host*,struct nlm_file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
nlm_inspect_file(struct nlm_host *host, struct nlm_file *file, nlm_host_match_fn_t match)
{
	nlmsvc_traverse_blocks(host, file, match);
	nlmsvc_traverse_shares(host, file, match);
	return nlm_traverse_locks(host, file, match);
}