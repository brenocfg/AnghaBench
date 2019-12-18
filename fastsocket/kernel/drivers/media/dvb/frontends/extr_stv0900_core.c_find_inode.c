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
typedef  scalar_t__ u8 ;
struct stv0900_inode {struct stv0900_inode* next_inode; TYPE_1__* internal; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_2__ {scalar_t__ i2c_addr; struct i2c_adapter* i2c_adap; } ;

/* Variables and functions */
 struct stv0900_inode* stv0900_first_inode ; 

__attribute__((used)) static struct stv0900_inode *find_inode(struct i2c_adapter *i2c_adap,
							u8 i2c_addr)
{
	struct stv0900_inode *temp_chip = stv0900_first_inode;

	if (temp_chip != NULL) {
		/*
		 Search of the last stv0900 chip or
		 find it by i2c adapter and i2c address */
		while ((temp_chip != NULL) &&
			((temp_chip->internal->i2c_adap != i2c_adap) ||
			(temp_chip->internal->i2c_addr != i2c_addr)))

			temp_chip = temp_chip->next_inode;

	}

	return temp_chip;
}