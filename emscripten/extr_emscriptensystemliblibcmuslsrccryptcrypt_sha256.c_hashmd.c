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
struct sha256 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sha256_update (struct sha256*,void const*,unsigned int) ; 

__attribute__((used)) static void hashmd(struct sha256 *s, unsigned int n, const void *md)
{
	unsigned int i;

	for (i = n; i > 32; i -= 32)
		sha256_update(s, md, 32);
	sha256_update(s, md, i);
}