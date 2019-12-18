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

__attribute__((used)) static int containsMergeSpecifier(const char *FilenamePat, int I) {
  return (FilenamePat[I] == 'm' ||
          (FilenamePat[I] >= '1' && FilenamePat[I] <= '9' &&
           /* If FilenamePat[I] is not '\0', the next byte is guaranteed
            * to be in-bound as the string is null terminated. */
           FilenamePat[I + 1] == 'm'));
}