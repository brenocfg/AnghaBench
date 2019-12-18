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
typedef  int /*<<< orphan*/  bvector ;

/* Variables and functions */
 int /*<<< orphan*/  VEC_ADDMANY (int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static void
vblob_append(void *cc, const void *data, size_t len)
{
	bvector *bv;

	bv = cc;
	VEC_ADDMANY(*bv, data, len);
}