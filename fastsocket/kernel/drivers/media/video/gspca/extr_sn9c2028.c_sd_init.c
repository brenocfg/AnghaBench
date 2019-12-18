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

/* Variables and functions */
 int sn9c2028_read1 (struct gspca_dev*) ; 

__attribute__((used)) static int sd_init(struct gspca_dev *gspca_dev)
{
	int status = -1;

	sn9c2028_read1(gspca_dev);
	sn9c2028_read1(gspca_dev);
	status = sn9c2028_read1(gspca_dev);

	return (status < 0) ? status : 0;
}