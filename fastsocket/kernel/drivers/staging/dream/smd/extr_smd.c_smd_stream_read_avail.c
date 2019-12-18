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
struct smd_channel {TYPE_1__* recv; } ;
struct TYPE_2__ {int head; int tail; } ;

/* Variables and functions */
 int SMD_BUF_SIZE ; 

__attribute__((used)) static int smd_stream_read_avail(struct smd_channel *ch)
{
	return (ch->recv->head - ch->recv->tail) & (SMD_BUF_SIZE - 1);
}