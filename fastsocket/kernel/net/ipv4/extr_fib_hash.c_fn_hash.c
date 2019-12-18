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
typedef  int u32 ;
struct fn_zone {int fz_order; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int FZ_HASHMASK (struct fn_zone*) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 fn_hash(__be32 key, struct fn_zone *fz)
{
	u32 h = ntohl(key)>>(32 - fz->fz_order);
	h ^= (h>>20);
	h ^= (h>>10);
	h ^= (h>>5);
	h &= FZ_HASHMASK(fz);
	return h;
}