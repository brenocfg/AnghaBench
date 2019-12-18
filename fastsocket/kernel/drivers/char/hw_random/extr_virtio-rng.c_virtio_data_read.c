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
typedef  int /*<<< orphan*/  u32 ;
struct hwrng {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int data_left ; 
 int /*<<< orphan*/  have_data ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * random_data ; 
 int /*<<< orphan*/  register_buffer () ; 

__attribute__((used)) static int virtio_data_read(struct hwrng *rng, u32 *data)
{
	BUG_ON(data_left < sizeof(u32));
	data_left -= sizeof(u32);
	*data = random_data[data_left / 4];

	if (data_left < sizeof(u32)) {
		init_completion(&have_data);
		register_buffer();
	}
	return sizeof(*data);
}