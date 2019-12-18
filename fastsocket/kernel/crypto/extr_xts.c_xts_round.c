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
struct sinfo {void* t; int /*<<< orphan*/  tfm; int /*<<< orphan*/  (* fn ) (int /*<<< orphan*/ ,void*,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  be128_xor (void*,void*,void const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*,void*) ; 

__attribute__((used)) static inline void xts_round(struct sinfo *s, void *dst, const void *src)
{
	be128_xor(dst, s->t, src);		/* PP <- T xor P */
	s->fn(s->tfm, dst, dst);		/* CC <- E(Key1,PP) */
	be128_xor(dst, dst, s->t);		/* C <- T xor CC */
}