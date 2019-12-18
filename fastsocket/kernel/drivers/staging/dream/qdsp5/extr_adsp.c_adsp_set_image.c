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
typedef  int /*<<< orphan*/  uint32_t ;
struct adsp_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_image ; 

void adsp_set_image(struct adsp_info *info, uint32_t image)
{
	current_image = image;
}