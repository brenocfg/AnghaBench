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

/* Variables and functions */
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  checkEntryByValue (char*,int,char const**) ; 
 int /*<<< orphan*/  checkEntryDatabase () ; 
 int /*<<< orphan*/  endprotoent () ; 
 int /*<<< orphan*/ * getprotobyname (char*) ; 
 int /*<<< orphan*/  puts (char*) ; 

int main() {
    // First check getprotobyname() and getprotobynumber()
    const char* aliases[] = {"TCP"};
    checkEntryByValue("tcp", 6, aliases);

    aliases[0] = "UDP";
    checkEntryByValue("udp", 17, aliases);

    // Check that the doomsday protocol hasn't been implemented :-) ......
    assert(getprotobyname("doomsday") == NULL);

    // Now check setprotoent() and getprotoent()
    checkEntryDatabase();

    endprotoent();

    puts("success");

    return EXIT_SUCCESS;
}