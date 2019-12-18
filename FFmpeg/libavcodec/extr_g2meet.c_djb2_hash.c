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
 int EPIC_HASH_SIZE ; 

__attribute__((used)) static int djb2_hash(uint32_t key)
{
    uint32_t h = 5381;

    h = (h * 33) ^ ((key >> 24) & 0xFF); // xxx: probably not needed at all
    h = (h * 33) ^ ((key >> 16) & 0xFF);
    h = (h * 33) ^ ((key >>  8) & 0xFF);
    h = (h * 33) ^  (key        & 0xFF);

    return h & (EPIC_HASH_SIZE - 1);
}