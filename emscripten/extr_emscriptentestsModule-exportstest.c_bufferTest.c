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
 int /*<<< orphan*/  printf (char*,int,...) ; 

void bufferTest(const void* source, unsigned int sourceLen) {
    int i = 0;
    unsigned char* src = (unsigned char*)source;

    printf("in test method: size of source buffer = %d\n", sourceLen);

    for (i = 0; i < sourceLen; i++) {
        printf("source[%d] = %d\n", i, src[i]);
    }
}