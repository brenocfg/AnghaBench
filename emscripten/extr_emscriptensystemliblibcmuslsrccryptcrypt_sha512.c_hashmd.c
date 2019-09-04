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
struct sha512 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sha512_update (struct sha512*,void const*,unsigned int) ; 

__attribute__((used)) static void hashmd(struct sha512 *s, unsigned int n, const void *md)
{
	unsigned int i;

	for (i = n; i > 64; i -= 64)
		sha512_update(s, md, 64);
	sha512_update(s, md, i);
}