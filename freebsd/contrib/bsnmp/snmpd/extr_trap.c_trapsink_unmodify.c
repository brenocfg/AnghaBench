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
struct trapsink_dep {int set; int /*<<< orphan*/  rb_comm; int /*<<< orphan*/  rb_version; int /*<<< orphan*/  rb_status; } ;
struct trapsink {int /*<<< orphan*/  comm; int /*<<< orphan*/  version; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int SNMP_ERR_NOERROR ; 
 int TDEP_COMM ; 
 int TDEP_STATUS ; 
 int TDEP_VERSION ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
trapsink_unmodify(struct trapsink *t, struct trapsink_dep *tdep)
{
	if (tdep->set & TDEP_STATUS)
		t->status = tdep->rb_status;
	if (tdep->set & TDEP_VERSION)
		t->version = tdep->rb_version;
	if (tdep->set & TDEP_COMM)
		strcpy(t->comm, tdep->rb_comm);

	return (SNMP_ERR_NOERROR);
}