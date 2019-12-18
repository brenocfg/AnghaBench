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
struct pwc_device {int /*<<< orphan*/ * decompress_data; } ;
struct pwc_dec1_private {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 

int pwc_dec1_alloc(struct pwc_device *pwc)
{
	pwc->decompress_data = kmalloc(sizeof(struct pwc_dec1_private), GFP_KERNEL);
	if (pwc->decompress_data == NULL)
		return -ENOMEM;
	return 0;
}