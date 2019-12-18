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
struct bfa_cee_stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_cee_stats_swap(struct bfa_cee_stats *stats)
{
	u32 *buffer = (u32 *)stats;
	int i;

	for (i = 0; i < (sizeof(struct bfa_cee_stats) / sizeof(u32));
		i++) {
		buffer[i] = ntohl(buffer[i]);
	}
}