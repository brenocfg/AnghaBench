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
struct s3c2410fb_info {scalar_t__ drv_type; } ;

/* Variables and functions */
 scalar_t__ DRV_S3C2412 ; 

__attribute__((used)) static int is_s3c2412(struct s3c2410fb_info *fbi)
{
	return (fbi->drv_type == DRV_S3C2412);
}