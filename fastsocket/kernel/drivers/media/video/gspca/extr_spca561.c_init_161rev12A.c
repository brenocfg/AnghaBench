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
 int /*<<< orphan*/  Pb100_1map8300 ; 
 int /*<<< orphan*/  Pb100_2map8300 ; 
 int /*<<< orphan*/  sensor_mapwrite (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spca561_161rev12A_data1 ; 
 int /*<<< orphan*/  spca561_161rev12A_data2 ; 
 int /*<<< orphan*/  write_vector (struct gspca_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_161rev12A(struct gspca_dev *gspca_dev)
{
	write_vector(gspca_dev, spca561_161rev12A_data1);
	sensor_mapwrite(gspca_dev, Pb100_1map8300);
/*fixme: should be in sd_start*/
	write_vector(gspca_dev, spca561_161rev12A_data2);
	sensor_mapwrite(gspca_dev, Pb100_2map8300);
}