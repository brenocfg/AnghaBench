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
struct addrinfo {scalar_t__ ai_family; struct addrinfo* ai_next; } ;

/* Variables and functions */

__attribute__((used)) static void interleave_addrinfo(struct addrinfo *base)
{
    struct addrinfo **next = &base->ai_next;
    while (*next) {
        struct addrinfo *cur = *next;
        // Iterate forward until we find an entry of a different family.
        if (cur->ai_family == base->ai_family) {
            next = &cur->ai_next;
            continue;
        }
        if (cur == base->ai_next) {
            // If the first one following base is of a different family, just
            // move base forward one step and continue.
            base = cur;
            next = &base->ai_next;
            continue;
        }
        // Unchain cur from the rest of the list from its current spot.
        *next = cur->ai_next;
        // Hook in cur directly after base.
        cur->ai_next = base->ai_next;
        base->ai_next = cur;
        // Restart with a new base. We know that before moving the cur element,
        // everything between the previous base and cur had the same family,
        // different from cur->ai_family. Therefore, we can keep next pointing
        // where it was, and continue from there with base at the one after
        // cur.
        base = cur->ai_next;
    }
}