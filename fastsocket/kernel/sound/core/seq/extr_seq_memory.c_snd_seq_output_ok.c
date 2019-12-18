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
struct snd_seq_pool {scalar_t__ room; } ;

/* Variables and functions */
 scalar_t__ snd_seq_pool_available (struct snd_seq_pool*) ; 

__attribute__((used)) static inline int snd_seq_output_ok(struct snd_seq_pool *pool)
{
	return snd_seq_pool_available(pool) >= pool->room;
}