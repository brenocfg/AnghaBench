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
struct lapb_register_struct {int /*<<< orphan*/  data_transmit; int /*<<< orphan*/  data_indication; void* disconnect_indication; void* disconnect_confirmation; void* connect_indication; void* connect_confirmation; } ;

/* Variables and functions */
 int LAPB_OK ; 
 int lapb_register (struct net_device*,struct lapb_register_struct*) ; 
 void* x25_connected ; 
 int /*<<< orphan*/  x25_data_indication ; 
 int /*<<< orphan*/  x25_data_transmit ; 
 void* x25_disconnected ; 

__attribute__((used)) static int x25_open(struct net_device *dev)
{
	struct lapb_register_struct cb;
	int result;

	cb.connect_confirmation = x25_connected;
	cb.connect_indication = x25_connected;
	cb.disconnect_confirmation = x25_disconnected;
	cb.disconnect_indication = x25_disconnected;
	cb.data_indication = x25_data_indication;
	cb.data_transmit = x25_data_transmit;

	result = lapb_register(dev, &cb);
	if (result != LAPB_OK)
		return result;
	return 0;
}