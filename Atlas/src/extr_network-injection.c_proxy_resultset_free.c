#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ fields; } ;
typedef  TYPE_1__ proxy_resultset_t ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  network_mysqld_proto_fielddefs_free (scalar_t__) ; 

void proxy_resultset_free(proxy_resultset_t *res) {
	if (!res) return;
    
	if (res->fields) {
		network_mysqld_proto_fielddefs_free(res->fields);
	}
    
	g_free(res);
}