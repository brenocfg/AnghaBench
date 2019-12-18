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
typedef  int /*<<< orphan*/  u16 ;
struct c67x00_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIEMSG_REG (int) ; 
 int /*<<< orphan*/  hpi_read_word (struct c67x00_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_write_word (struct c67x00_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u16 c67x00_ll_fetch_siemsg(struct c67x00_device *dev, int sie_num)
{
	u16 val;

	val = hpi_read_word(dev, SIEMSG_REG(sie_num));
	/* clear register to allow next message */
	hpi_write_word(dev, SIEMSG_REG(sie_num), 0);

	return val;
}