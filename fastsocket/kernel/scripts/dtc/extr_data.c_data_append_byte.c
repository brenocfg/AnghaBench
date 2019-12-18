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
typedef  int /*<<< orphan*/  uint8_t ;
struct data {int dummy; } ;

/* Variables and functions */
 struct data data_append_data (struct data,int /*<<< orphan*/ *,int) ; 

struct data data_append_byte(struct data d, uint8_t byte)
{
	return data_append_data(d, &byte, 1);
}