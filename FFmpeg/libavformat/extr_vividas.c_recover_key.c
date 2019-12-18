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
 int AV_RL32 (unsigned char*) ; 
 int /*<<< orphan*/  put_v (unsigned char*,unsigned int) ; 

__attribute__((used)) static unsigned recover_key(unsigned char sample[4], unsigned expected_size)
{
    unsigned char plaintext[8] = { 'S', 'B' };

    put_v(plaintext+2, expected_size);

    return AV_RL32(sample) ^ AV_RL32(plaintext);
}