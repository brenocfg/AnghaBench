#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  rp; int /*<<< orphan*/  dp; } ;
struct TYPE_5__ {size_t num_name_elts; char const* server_name; TYPE_3__ cpu; int /*<<< orphan*/  rp_stack; int /*<<< orphan*/  dp_stack; scalar_t__ err; scalar_t__ num_certs; int /*<<< orphan*/  pkey; TYPE_1__* name_elts; } ;
typedef  TYPE_2__ br_x509_minimal_context ;
typedef  int /*<<< orphan*/  br_x509_class ;
struct TYPE_4__ {scalar_t__* buf; scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_x509_minimal_init_main (TYPE_3__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
xm_start_chain(const br_x509_class **ctx, const char *server_name)
{
	br_x509_minimal_context *cc;
	size_t u;

	cc = (br_x509_minimal_context *)(void *)ctx;
	for (u = 0; u < cc->num_name_elts; u ++) {
		cc->name_elts[u].status = 0;
		cc->name_elts[u].buf[0] = 0;
	}
	memset(&cc->pkey, 0, sizeof cc->pkey);
	cc->num_certs = 0;
	cc->err = 0;
	cc->cpu.dp = cc->dp_stack;
	cc->cpu.rp = cc->rp_stack;
	br_x509_minimal_init_main(&cc->cpu);
	if (server_name == NULL || *server_name == 0) {
		cc->server_name = NULL;
	} else {
		cc->server_name = server_name;
	}
}