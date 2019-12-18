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
typedef  int /*<<< orphan*/  htab_entry_t ;

/* Variables and functions */
 int SH2REC_HTAB_ENTRIES ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  table ; 

void sh2rec_htab_init(void) {
    memset(table, 0, sizeof(htab_entry_t *) * SH2REC_HTAB_ENTRIES);
}