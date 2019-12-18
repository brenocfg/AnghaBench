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
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  get_bits_long (int /*<<< orphan*/ *,int) ; 
 int sign_extend (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int get_sbits_long(GetBitContext *s, int n)
{
    // sign_extend(x, 0) is undefined
    if (!n)
        return 0;

    return sign_extend(get_bits_long(s, n), n);
}