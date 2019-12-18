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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_PORT ; 
 int HI_NIBBLE ; 
 int NULL_COMMAND ; 
 int STATUS ; 
 int /*<<< orphan*/  STATUS_PORT ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 de600_read_status(struct net_device *dev)
{
	u8 status;

	outb_p(STATUS, DATA_PORT);
	status = inb(STATUS_PORT);
	outb_p(NULL_COMMAND | HI_NIBBLE, DATA_PORT);

	return status;
}