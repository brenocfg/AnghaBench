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
 size_t kDTMaxEntryNameLength ; 
 char const kDTPathNameSeparator ; 

__attribute__((used)) static const char *
GetNextComponent(const char *cp, char *bp)
{
	size_t length = 0;
	char *origbp = bp;

	while (*cp != 0) {
		if (*cp == kDTPathNameSeparator) {
			cp++;
			break;
		}
		if (++length > kDTMaxEntryNameLength) {
			*origbp = '\0';
			return cp;
		}
		*bp++ = *cp++;
	}
	*bp = 0;
	return cp;
}