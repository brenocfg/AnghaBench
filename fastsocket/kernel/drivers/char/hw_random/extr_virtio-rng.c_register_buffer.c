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
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ RANDOM_DATA_SIZE ; 
 scalar_t__ data_left ; 
 scalar_t__ random_data ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,scalar_t__,scalar_t__) ; 
 scalar_t__ virtqueue_add_buf (int /*<<< orphan*/ ,struct scatterlist*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  virtqueue_kick (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vq ; 

__attribute__((used)) static void register_buffer(void)
{
	struct scatterlist sg;

	sg_init_one(&sg, random_data+data_left, RANDOM_DATA_SIZE-data_left);
	/* There should always be room for one buffer. */
	if (virtqueue_add_buf(vq, &sg, 0, 1, random_data) < 0)
		BUG();

	virtqueue_kick(vq);
}