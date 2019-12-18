#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  l3num; } ;
struct TYPE_6__ {TYPE_1__ src; } ;
struct TYPE_7__ {TYPE_2__ tuple; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_conntrack_helper_unregister (TYPE_3__*) ; 
 int /*<<< orphan*/ * ports ; 
 int ports_c ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__** sane ; 
 int /*<<< orphan*/  sane_buffer ; 

__attribute__((used)) static void nf_conntrack_sane_fini(void)
{
	int i, j;

	for (i = 0; i < ports_c; i++) {
		for (j = 0; j < 2; j++) {
			pr_debug("nf_ct_sane: unregistering helper for pf: %d "
				 "port: %d\n",
				 sane[i][j].tuple.src.l3num, ports[i]);
			nf_conntrack_helper_unregister(&sane[i][j]);
		}
	}

	kfree(sane_buffer);
}