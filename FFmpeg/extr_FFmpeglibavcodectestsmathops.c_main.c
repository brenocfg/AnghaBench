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
 unsigned int ff_sqrt (unsigned int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stderr ; 

int main(void)
{
    unsigned u;

    for(u=0; u<65536; u++) {
        unsigned s = u*u;
        unsigned root = ff_sqrt(s);
        unsigned root_m1 = ff_sqrt(s-1);
        if (s && root != u) {
            fprintf(stderr, "ff_sqrt failed at %u with %u\n", s, root);
            return 1;
        }
        if (u && root_m1 != u - 1) {
            fprintf(stderr, "ff_sqrt failed at %u with %u\n", s, root);
            return 1;
        }
    }
    return 0;
}