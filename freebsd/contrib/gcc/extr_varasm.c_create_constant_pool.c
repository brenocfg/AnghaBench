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
struct rtx_constant_pool {scalar_t__ offset; int /*<<< orphan*/ * last; int /*<<< orphan*/ * first; int /*<<< orphan*/  const_rtx_htab; } ;

/* Variables and functions */
 int /*<<< orphan*/  const_desc_rtx_eq ; 
 int /*<<< orphan*/  const_desc_rtx_hash ; 
 struct rtx_constant_pool* ggc_alloc (int) ; 
 int /*<<< orphan*/  htab_create_ggc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct rtx_constant_pool *
create_constant_pool (void)
{
  struct rtx_constant_pool *pool;

  pool = ggc_alloc (sizeof (struct rtx_constant_pool));
  pool->const_rtx_htab = htab_create_ggc (31, const_desc_rtx_hash,
					  const_desc_rtx_eq, NULL);
  pool->first = NULL;
  pool->last = NULL;
  pool->offset = 0;
  return pool;
}