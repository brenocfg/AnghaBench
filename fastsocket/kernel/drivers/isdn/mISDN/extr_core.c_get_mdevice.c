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
typedef  int /*<<< orphan*/  u_int ;
struct mISDNdevice {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _get_mdevice ; 
 int /*<<< orphan*/  class_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mISDNdevice* dev_to_mISDN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mISDN_class ; 

struct mISDNdevice
*get_mdevice(u_int id)
{
	return dev_to_mISDN(class_find_device(&mISDN_class, NULL, &id,
		_get_mdevice));
}