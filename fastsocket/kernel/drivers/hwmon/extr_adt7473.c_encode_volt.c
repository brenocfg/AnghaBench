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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int SCALE (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SENSORS_LIMIT (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * adt7473_scaling ; 

__attribute__((used)) static u8 encode_volt(int volt_index, int cooked)
{
	int raw = SCALE(cooked, adt7473_scaling[volt_index], 192);
	return SENSORS_LIMIT(raw, 0, 255);
}