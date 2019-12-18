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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void printRegbitsRange(char* buffer, uint32_t data, const char* prefix)
{
	unsigned int first = 0;
	unsigned int run_length = 0;
	int i;

	for (i = 0; i < 8; ++i) {
		if (data & (1 << i)) {
			first = i;
			run_length = 0;

			while (i < 7 && (data & (1 << (i + 1)))) {
				i++;
				run_length++;
			}

			if (buffer[0] != 0)
				strcat(buffer, "/");

			sprintf(buffer + strlen(buffer), "%s%d", prefix, first);
			if (run_length > 0)
				sprintf(buffer + strlen(buffer), "-%s%d", prefix, first + run_length);
		}
	}
}