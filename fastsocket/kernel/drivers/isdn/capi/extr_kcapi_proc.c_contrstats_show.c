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
struct capi_ctr {int /*<<< orphan*/  nsentdatapkt; int /*<<< orphan*/  nsentctlpkt; int /*<<< orphan*/  nrecvdatapkt; int /*<<< orphan*/  nrecvctlpkt; int /*<<< orphan*/  cnr; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int contrstats_show(struct seq_file *seq, void *v)
{
	struct capi_ctr *ctr = *(struct capi_ctr **) v;

	if (!ctr)
		return 0;

	seq_printf(seq, "%d %lu %lu %lu %lu\n",
		   ctr->cnr, 
		   ctr->nrecvctlpkt,
		   ctr->nrecvdatapkt,
		   ctr->nsentctlpkt,
		   ctr->nsentdatapkt);

	return 0;
}