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
struct sha256_ctx {int /*<<< orphan*/ * h; } ;

/* Variables and functions */
 int /*<<< orphan*/  store32be (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sha256_subhash(struct sha256_ctx *p, uint32_t *t)
{
   unsigned i;
   for (i = 0; i < 8; i++)
      store32be(t++, p->h[i]);
}