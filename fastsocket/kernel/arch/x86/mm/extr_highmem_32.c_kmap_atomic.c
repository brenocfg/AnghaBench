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
struct page {int dummy; } ;
typedef  enum km_type { ____Placeholder_km_type } km_type ;

/* Variables and functions */
 void* kmap_atomic_prot (struct page*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmap_prot ; 

void *kmap_atomic(struct page *page, enum km_type type)
{
	return kmap_atomic_prot(page, type, kmap_prot);
}