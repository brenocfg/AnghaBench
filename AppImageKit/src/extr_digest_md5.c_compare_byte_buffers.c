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

bool compare_byte_buffers(const char* buf1, const char* buf2, size_t num_bytes) {
    for (size_t i = 0; i < num_bytes; i++) {
        if (buf1[i] != buf2[i]) {
            return false;
        }
    }

    return true;
}