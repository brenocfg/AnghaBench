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
typedef  int /*<<< orphan*/  bitbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  bits_get (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int bits_skip(bitbuf_t *bb, int bits)
{
    if (bits <= 0)
        return 0;
    while (bits > 32)
    {
        bits_get(bb, 32);
        bits -= 32;
    }
    bits_get(bb, bits);
    return 0;
}