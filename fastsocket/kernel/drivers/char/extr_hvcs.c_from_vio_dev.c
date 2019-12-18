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
struct vio_dev {int /*<<< orphan*/  dev; } ;
struct hvcs_struct {int dummy; } ;

/* Variables and functions */
 struct hvcs_struct* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct hvcs_struct *from_vio_dev(struct vio_dev *viod)
{
	return dev_get_drvdata(&viod->dev);
}