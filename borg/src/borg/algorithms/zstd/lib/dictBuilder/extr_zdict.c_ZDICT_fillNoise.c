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

__attribute__((used)) static void ZDICT_fillNoise(void* buffer, size_t length)
{
    unsigned const prime1 = 2654435761U;
    unsigned const prime2 = 2246822519U;
    unsigned acc = prime1;
    size_t p=0;;
    for (p=0; p<length; p++) {
        acc *= prime2;
        ((unsigned char*)buffer)[p] = (unsigned char)(acc >> 21);
    }
}