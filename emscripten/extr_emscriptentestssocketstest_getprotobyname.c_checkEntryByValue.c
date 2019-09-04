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
struct protoent {char const* p_name; int p_proto; char** p_aliases; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct protoent* getprotobyname (char const*) ; 
 struct protoent* getprotobynumber (int) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

void checkEntryByValue(const char* name, int port, const char** aliasArray) {
    struct protoent* entry;
    char** aliases;

    // Perform a protocol look up by name
    entry = getprotobyname(name);
    assert(entry != NULL);

    // Check results
    assert(strcmp(name, entry->p_name) == 0);
    assert(port == entry->p_proto);

    aliases = entry->p_aliases;
    for (int i = 0; aliases[i] != NULL; i++) {
        assert(strcmp(aliases[i], aliasArray[i]) == 0);
    }

    // Perform a protocol look up by number
    entry = getprotobynumber(port);
    assert(entry != NULL);

    // Check results
    assert(strcmp(name, entry->p_name) == 0);
    assert(port == entry->p_proto);

    aliases = entry->p_aliases;
    for (int i = 0; aliases[i] != NULL; i++) {
        assert(strcmp(aliases[i], aliasArray[i]) == 0);
    }
}