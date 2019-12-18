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
struct lm90_data {int flags; } ;

/* Variables and functions */
 int LM90_FLAG_ADT7461_EXT ; 
 int temp_from_s8 (int) ; 

__attribute__((used)) static inline int temp_from_u8_adt7461(struct lm90_data *data, u8 val)
{
	if (data->flags & LM90_FLAG_ADT7461_EXT)
		return (val - 64) * 1000;
	else
		return temp_from_s8(val);
}