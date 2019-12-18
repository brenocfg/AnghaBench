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
typedef  size_t uint8_t ;

/* Variables and functions */
 unsigned int Nb ; 
 unsigned int Nk ; 
 size_t* sbox ; 

__attribute__((used)) static inline void sub_bytes(uint8_t *s)
{
    unsigned int i;

    for (i = 0; i < (Nb * Nk); ++i) {
        s[i] = sbox[s[i]];
    }
}