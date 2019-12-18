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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct parisc_device_id {scalar_t__ sversion; scalar_t__ hversion_rev; scalar_t__ hversion; scalar_t__ hw_type; } ;
struct parisc_device {struct parisc_device_id id; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int) ; 
 struct parisc_device* to_parisc_device (struct device*) ; 

__attribute__((used)) static ssize_t make_modalias(struct device *dev, char *buf)
{
	const struct parisc_device *padev = to_parisc_device(dev);
	const struct parisc_device_id *id = &padev->id;

	return sprintf(buf, "parisc:t%02Xhv%04Xrev%02Xsv%08X\n",
		(u8)id->hw_type, (u16)id->hversion, (u8)id->hversion_rev,
		(u32)id->sversion);
}