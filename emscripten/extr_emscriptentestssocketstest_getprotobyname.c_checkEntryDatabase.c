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
struct protoent {int /*<<< orphan*/  p_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct protoent* getprotoent () ; 
 int /*<<< orphan*/  setprotoent (int) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

void checkEntryDatabase() {
    struct protoent* entry;

    // Don't call setprotoent() initially as getprotoent() should open the "database" if necessary.
    entry = getprotoent();
    assert(entry != NULL);
    assert(strcmp("tcp", entry->p_name) == 0);

    entry = getprotoent();
    assert(entry != NULL);
    assert(strcmp("udp", entry->p_name) == 0);

    // Check that setprotoent() correctly sets the next entry to the first entry
    setprotoent(1);

    entry = getprotoent();
    assert(entry != NULL);
    assert(strcmp("tcp", entry->p_name) == 0);

    entry = getprotoent();
    assert(entry != NULL);
    assert(strcmp("udp", entry->p_name) == 0);

    // If we do a getprotoent() that goes past the end of the 'database' check that it returns NULL.
    entry = getprotoent();
    assert(entry == NULL);
}