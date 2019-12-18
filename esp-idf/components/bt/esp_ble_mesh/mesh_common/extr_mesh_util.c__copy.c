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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 unsigned int TC_CRYPTO_FAIL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 

unsigned int _copy(uint8_t *to, unsigned int to_len,
                   const uint8_t *from, unsigned int from_len)
{
    if (from_len <= to_len) {
        (void)memcpy(to, from, from_len);
        return from_len;
    } else {
        return TC_CRYPTO_FAIL;
    }
}