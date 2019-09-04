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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline uint32_t latm_get_value(GetBitContext *b)
{
    int length = get_bits(b, 2);

    return get_bits_long(b, (length+1)*8);
}