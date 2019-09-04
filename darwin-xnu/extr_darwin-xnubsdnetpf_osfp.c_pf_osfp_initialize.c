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
struct pf_osfp_entry {int dummy; } ;
struct pf_os_fingerprint {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pf_osfp_entry_pl ; 
 int /*<<< orphan*/  pf_osfp_list ; 
 int /*<<< orphan*/  pf_osfp_pl ; 
 int /*<<< orphan*/  pool_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

void
pf_osfp_initialize(void)
{
	pool_init(&pf_osfp_entry_pl, sizeof (struct pf_osfp_entry), 0, 0, 0,
	    "pfosfpen", NULL);
	pool_init(&pf_osfp_pl, sizeof (struct pf_os_fingerprint), 0, 0, 0,
	    "pfosfp", NULL);
	SLIST_INIT(&pf_osfp_list);
}