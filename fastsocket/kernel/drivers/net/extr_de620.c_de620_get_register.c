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
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  W_DUMMY ; 
 int /*<<< orphan*/  de620_read_byte (struct net_device*) ; 
 int /*<<< orphan*/  de620_send_command (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline byte
de620_get_register(struct net_device *dev, byte reg)
{
	byte value;

	de620_send_command(dev,reg);
	value = de620_read_byte(dev);
	de620_send_command(dev,W_DUMMY);

	return value;
}