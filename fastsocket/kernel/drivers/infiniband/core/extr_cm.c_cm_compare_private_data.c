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
typedef  int /*<<< orphan*/  u8 ;
struct ib_cm_compare_data {int /*<<< orphan*/  data; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int IB_CM_COMPARE_SIZE ; 
 int /*<<< orphan*/  cm_mask_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cm_compare_private_data(u8 *private_data,
				   struct ib_cm_compare_data *dst_data)
{
	u8 src[IB_CM_COMPARE_SIZE];

	if (!dst_data)
		return 0;

	cm_mask_copy(src, private_data, dst_data->mask);
	return memcmp(src, dst_data->data, IB_CM_COMPARE_SIZE);
}