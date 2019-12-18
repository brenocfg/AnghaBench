#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * set_info; } ;
typedef  TYPE_1__ example_fast_prov_server_t ;

/* Variables and functions */
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void example_free_set_info(example_fast_prov_server_t *srv)
{
    if (srv && srv->set_info) {
        osi_free(srv->set_info);
        srv->set_info = NULL;
    }
}