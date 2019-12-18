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
struct gss_api_mech {int /*<<< orphan*/ * gm_upcall_enctypes; } ;

/* Variables and functions */
 struct gss_api_mech* gss_mech_get_by_name (char*) ; 
 int /*<<< orphan*/  gss_mech_put (struct gss_api_mech*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int supported_enctypes_show(struct seq_file *m, void *v)
{
	struct gss_api_mech *k5mech;

	k5mech = gss_mech_get_by_name("krb5");
	if (k5mech == NULL)
		goto out;
	if (k5mech->gm_upcall_enctypes != NULL)
		seq_printf(m, k5mech->gm_upcall_enctypes);
	gss_mech_put(k5mech);
out:
	return 0;
}