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
struct ixp2000_uengine_code {int cpu_model_bitmask; int cpu_min_revision; int cpu_max_revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXP_PRODUCT_ID ; 
 int ixp2000_reg_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_ixp_type(struct ixp2000_uengine_code *c)
{
	u32 product_id;
	u32 rev;

	product_id = ixp2000_reg_read(IXP_PRODUCT_ID);
	if (((product_id >> 16) & 0x1f) != 0)
		return 0;

	switch ((product_id >> 8) & 0xff) {
#ifdef CONFIG_ARCH_IXP2000
	case 0:		/* IXP2800 */
		if (!(c->cpu_model_bitmask & 4))
			return 0;
		break;

	case 1:		/* IXP2850 */
		if (!(c->cpu_model_bitmask & 8))
			return 0;
		break;

	case 2:		/* IXP2400 */
		if (!(c->cpu_model_bitmask & 2))
			return 0;
		break;
#endif

#ifdef CONFIG_ARCH_IXP23XX
	case 4:		/* IXP23xx */
		if (!(c->cpu_model_bitmask & 0x3f0))
			return 0;
		break;
#endif

	default:
		return 0;
	}

	rev = product_id & 0xff;
	if (rev < c->cpu_min_revision || rev > c->cpu_max_revision)
		return 0;

	return 1;
}