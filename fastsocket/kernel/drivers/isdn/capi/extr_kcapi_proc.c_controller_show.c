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
struct seq_file {int dummy; } ;
struct capi_ctr {char* (* procinfo ) (struct capi_ctr*) ;int /*<<< orphan*/  name; int /*<<< orphan*/  cardstate; int /*<<< orphan*/  driver_name; int /*<<< orphan*/  cnr; } ;

/* Variables and functions */
 int /*<<< orphan*/  cardstate2str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* stub1 (struct capi_ctr*) ; 

__attribute__((used)) static int controller_show(struct seq_file *seq, void *v)
{
	struct capi_ctr *ctr = *(struct capi_ctr **) v;

	if (!ctr)
		return 0;

	seq_printf(seq, "%d %-10s %-8s %-16s %s\n",
		   ctr->cnr, ctr->driver_name,
		   cardstate2str(ctr->cardstate),
		   ctr->name,
		   ctr->procinfo ?  ctr->procinfo(ctr) : "");

	return 0;
}