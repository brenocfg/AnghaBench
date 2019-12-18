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
typedef  enum plip_nibble_state { ____Placeholder_plip_nibble_state } plip_nibble_state ;

/* Variables and functions */
 int OK ; 
 int /*<<< orphan*/  PLIP_DELAY_UNIT ; 
#define  PLIP_NB_1 130 
#define  PLIP_NB_2 129 
#define  PLIP_NB_BEGIN 128 
 int TIMEOUT ; 
 unsigned char read_status (struct net_device*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_data (struct net_device*,unsigned char) ; 

__attribute__((used)) static inline int
plip_send(unsigned short nibble_timeout, struct net_device *dev,
	  enum plip_nibble_state *ns_p, unsigned char data)
{
	unsigned char c0;
	unsigned int cx;

	switch (*ns_p) {
	case PLIP_NB_BEGIN:
		write_data (dev, data & 0x0f);
		*ns_p = PLIP_NB_1;

	case PLIP_NB_1:
		write_data (dev, 0x10 | (data & 0x0f));
		cx = nibble_timeout;
		while (1) {
			c0 = read_status(dev);
			if ((c0 & 0x80) == 0)
				break;
			if (--cx == 0)
				return TIMEOUT;
			udelay(PLIP_DELAY_UNIT);
		}
		write_data (dev, 0x10 | (data >> 4));
		*ns_p = PLIP_NB_2;

	case PLIP_NB_2:
		write_data (dev, (data >> 4));
		cx = nibble_timeout;
		while (1) {
			c0 = read_status(dev);
			if (c0 & 0x80)
				break;
			if (--cx == 0)
				return TIMEOUT;
			udelay(PLIP_DELAY_UNIT);
		}
		*ns_p = PLIP_NB_BEGIN;
		return OK;
	}
	return OK;
}