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
typedef  int /*<<< orphan*/  bit_stream ;

/* Variables and functions */
 int /*<<< orphan*/  bit_advance (int /*<<< orphan*/ *,int,unsigned char**) ; 
 unsigned long bit_peek (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned long bit_read (bit_stream *bs, unsigned long mask,
			       int n, unsigned char **p) {
    unsigned long result = bit_peek (bs, mask);
    bit_advance (bs, n, p);
    return result;
}