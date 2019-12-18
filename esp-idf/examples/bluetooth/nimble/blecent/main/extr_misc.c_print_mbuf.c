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
struct os_mbuf {int om_len; int /*<<< orphan*/ * om_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  MODLOG_DFLT (int /*<<< orphan*/ ,char*,...) ; 
 struct os_mbuf* SLIST_NEXT (struct os_mbuf const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  om_next ; 

void
print_mbuf(const struct os_mbuf *om)
{
    int colon, i;

    colon = 0;
    while (om != NULL) {
        if (colon) {
            MODLOG_DFLT(INFO, ":");
        } else {
            colon = 1;
        }
        for (i = 0; i < om->om_len; i++) {
            MODLOG_DFLT(INFO, "%s0x%02x", i != 0 ? ":" : "", om->om_data[i]);
        }
        om = SLIST_NEXT(om, om_next);
    }
}