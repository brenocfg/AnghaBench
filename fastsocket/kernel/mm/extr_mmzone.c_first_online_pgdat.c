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
struct pglist_data {int dummy; } ;

/* Variables and functions */
 struct pglist_data* NODE_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  first_online_node ; 

struct pglist_data *first_online_pgdat(void)
{
	return NODE_DATA(first_online_node);
}