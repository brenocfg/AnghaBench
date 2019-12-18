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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
print_hashes(unsigned chashes)
{
	int i;

	for (i = 2; i <= 6; i ++) {
		if ((chashes >> i) & 1) {
			int z;

			switch (i) {
			case 3: z = 224; break;
			case 4: z = 256; break;
			case 5: z = 384; break;
			case 6: z = 512; break;
			default:
				z = 1;
				break;
			}
			fprintf(stderr, " sha%d", z);
		}
	}
}