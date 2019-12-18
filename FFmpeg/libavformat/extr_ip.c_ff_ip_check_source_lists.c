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
struct sockaddr_storage {int dummy; } ;
struct TYPE_3__ {int nb_exclude_addrs; int nb_include_addrs; int /*<<< orphan*/ * include_addrs; int /*<<< orphan*/ * exclude_addrs; } ;
typedef  TYPE_1__ IPSourceFilters ;

/* Variables and functions */
 int /*<<< orphan*/  compare_addr (struct sockaddr_storage*,int /*<<< orphan*/ *) ; 

int ff_ip_check_source_lists(struct sockaddr_storage *source_addr_ptr, IPSourceFilters *s)
{
    int i;
    if (s->nb_exclude_addrs) {
        for (i = 0; i < s->nb_exclude_addrs; i++) {
            if (!compare_addr(source_addr_ptr, &s->exclude_addrs[i]))
                return 1;
        }
    }
    if (s->nb_include_addrs) {
        for (i = 0; i < s->nb_include_addrs; i++) {
            if (!compare_addr(source_addr_ptr, &s->include_addrs[i]))
                return 0;
        }
        return 1;
    }
    return 0;
}