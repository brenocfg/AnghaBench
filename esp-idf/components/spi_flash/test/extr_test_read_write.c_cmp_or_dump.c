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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int memcmp (void const*,void const*,size_t) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int cmp_or_dump(const void *a, const void *b, size_t len)
{
    int r = memcmp(a, b, len);
    if (r != 0) {
        for (int i = 0; i < len; i++) {
            fprintf(stderr, "%02x", ((unsigned char *) a)[i]);
        }
        fprintf(stderr, "\n");
        for (int i = 0; i < len; i++) {
            fprintf(stderr, "%02x", ((unsigned char *) b)[i]);
        }
        fprintf(stderr, "\n");
    }
    return r;
}