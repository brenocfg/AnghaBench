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

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NPE_QLEN ; 
 int /*<<< orphan*/  crypt_phys ; 
 int /*<<< orphan*/  crypt_virt ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int setup_crypt_desc(void)
{
	BUILD_BUG_ON(sizeof(struct crypt_ctl) != 64);
	crypt_virt = dma_alloc_coherent(dev,
			NPE_QLEN * sizeof(struct crypt_ctl),
			&crypt_phys, GFP_KERNEL);
	if (!crypt_virt)
		return -ENOMEM;
	memset(crypt_virt, 0, NPE_QLEN * sizeof(struct crypt_ctl));
	return 0;
}