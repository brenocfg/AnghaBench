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
typedef  int UWORD ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 scalar_t__ get_hex2 (int*,int*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int get_attrib_range(UWORD *addr1, UWORD *addr2)
{
	if (get_hex2(addr1, addr2) && *addr1 <= *addr2) {
#ifdef PAGED_ATTRIB
		if ((*addr1 & 0xff) != 0 || (*addr2 & 0xff) != 0xff) {
			printf("This is PAGED_ATTRIB version of Atari800.\n"
			       "You can only change attributes of full memory pages.\n");
			return FALSE;
		}
#endif
		return TRUE;
	}
	printf("Missing or bad argument!\n");
	return FALSE;
}