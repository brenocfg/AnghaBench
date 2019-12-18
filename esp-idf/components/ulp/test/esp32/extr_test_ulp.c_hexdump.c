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
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void hexdump(const uint32_t* src, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        printf("%08x ", *src);
        ++src;
        if ((i + 1) % 4 == 0) {
            printf("\n");
        }
    }
}