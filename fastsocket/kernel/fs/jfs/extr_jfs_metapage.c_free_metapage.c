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
struct metapage {scalar_t__ flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  META_free ; 
 int /*<<< orphan*/  mempool_free (struct metapage*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metapage_mempool ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static inline void free_metapage(struct metapage *mp)
{
	mp->flag = 0;
	set_bit(META_free, &mp->flag);

	mempool_free(mp, metapage_mempool);
}