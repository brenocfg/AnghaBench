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
struct sd {scalar_t__ subtype; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ Nxultra ; 
 int /*<<< orphan*/  spca505_init_data ; 
 int /*<<< orphan*/  spca505b_init_data ; 
 scalar_t__ write_vector (struct gspca_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_init(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (write_vector(gspca_dev,
			 sd->subtype == Nxultra
				? spca505b_init_data
				: spca505_init_data))
		return -EIO;
	return 0;
}