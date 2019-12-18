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
typedef  int u16 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MT9M111_PAGE_MAP ; 
 int i2c_smbus_write_word_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swab16 (int) ; 

__attribute__((used)) static int reg_page_map_set(struct i2c_client *client, const u16 reg)
{
	int ret;
	u16 page;
	static int lastpage = -1;	/* PageMap cache value */

	page = (reg >> 8);
	if (page == lastpage)
		return 0;
	if (page > 2)
		return -EINVAL;

	ret = i2c_smbus_write_word_data(client, MT9M111_PAGE_MAP, swab16(page));
	if (!ret)
		lastpage = page;
	return ret;
}