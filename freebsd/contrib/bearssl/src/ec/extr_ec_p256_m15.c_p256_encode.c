#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ p256_jacobian ;

/* Variables and functions */
 int /*<<< orphan*/  le13_to_be8 (unsigned char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
p256_encode(void *dst, const p256_jacobian *P)
{
	unsigned char *buf;

	buf = dst;
	buf[0] = 0x04;
	le13_to_be8(buf + 1, 32, P->x);
	le13_to_be8(buf + 33, 32, P->y);
}