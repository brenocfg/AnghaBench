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
struct gspca_dev {int dummy; } ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int const*,int) ; 

__attribute__((used)) static int sd_init(struct gspca_dev *gspca_dev)
{
	const __u8 stop = 0x09; /* Disable stream turn of LED */

	reg_w(gspca_dev, 0x01, &stop, 1);

	return 0;
}