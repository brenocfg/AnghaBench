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
struct crypt_ctl {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ crypt_phys ; 
 struct crypt_ctl* crypt_virt ; 

__attribute__((used)) static inline dma_addr_t crypt_virt2phys(struct crypt_ctl *virt)
{
	return crypt_phys + (virt - crypt_virt) * sizeof(struct crypt_ctl);
}