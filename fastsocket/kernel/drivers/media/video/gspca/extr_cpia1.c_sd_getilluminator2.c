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
typedef  int /*<<< orphan*/  __s32 ;

/* Variables and functions */
 int sd_getilluminator (struct gspca_dev*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sd_getilluminator2(struct gspca_dev *gspca_dev, __s32 *val)
{
	return sd_getilluminator(gspca_dev, val, 2);
}