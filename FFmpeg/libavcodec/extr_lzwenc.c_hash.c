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
 int const LZW_HASH_SHIFT ; 
 int LZW_HASH_SIZE ; 
 int /*<<< orphan*/  av_assert2 (int) ; 

__attribute__((used)) static inline int hash(int head, const int add)
{
    head ^= (add << LZW_HASH_SHIFT);
    if (head >= LZW_HASH_SIZE)
        head -= LZW_HASH_SIZE;
    av_assert2(head >= 0 && head < LZW_HASH_SIZE);
    return head;
}