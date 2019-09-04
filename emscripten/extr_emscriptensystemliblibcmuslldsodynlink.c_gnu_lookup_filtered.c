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
typedef  int uint32_t ;
struct dso {int dummy; } ;
typedef  int /*<<< orphan*/  Sym ;

/* Variables and functions */
 int /*<<< orphan*/ * gnu_lookup (int,int*,struct dso*,char const*) ; 

__attribute__((used)) static Sym *gnu_lookup_filtered(uint32_t h1, uint32_t *hashtab, struct dso *dso, const char *s, uint32_t fofs, size_t fmask)
{
	const size_t *bloomwords = (const void *)(hashtab+4);
	size_t f = bloomwords[fofs & (hashtab[2]-1)];
	if (!(f & fmask)) return 0;

	f >>= (h1 >> hashtab[3]) % (8 * sizeof f);
	if (!(f & 1)) return 0;

	return gnu_lookup(h1, hashtab, dso, s);
}