#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct zoran {int dummy; } ;
struct videocodec {TYPE_1__* master_data; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ post_office_wait (struct zoran*) ; 
 scalar_t__ post_office_write (struct zoran*,int,int,int) ; 

__attribute__((used)) static void
zr36050_write (struct videocodec *codec,
	       u16                reg,
	       u32                val)
{
	struct zoran *zr = (struct zoran *) codec->master_data->data;

	if (post_office_wait(zr)
	    || post_office_write(zr, 1, 0, reg >> 2)) {	// reg. HIGHBYTES
		return;
	}

	post_office_write(zr, 0, reg & 0x03, val & 0xff);	// reg. LOWBYTES + wr. data
}