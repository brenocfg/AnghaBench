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
struct rds_cong_map {scalar_t__* m_page_addrs; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 unsigned long RDS_CONG_MAP_PAGE_BITS ; 
 unsigned long be16_to_cpu (int /*<<< orphan*/ ) ; 
 int test_bit_le (unsigned long,void*) ; 

__attribute__((used)) static int rds_cong_test_bit(struct rds_cong_map *map, __be16 port)
{
	unsigned long i;
	unsigned long off;

	i = be16_to_cpu(port) / RDS_CONG_MAP_PAGE_BITS;
	off = be16_to_cpu(port) % RDS_CONG_MAP_PAGE_BITS;

	return test_bit_le(off, (void *)map->m_page_addrs[i]);
}