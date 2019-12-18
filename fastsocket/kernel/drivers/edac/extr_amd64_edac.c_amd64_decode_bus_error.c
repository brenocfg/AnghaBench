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
struct mce {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __amd64_decode_bus_error (int /*<<< orphan*/ ,struct mce*) ; 
 int /*<<< orphan*/ * mcis ; 

void amd64_decode_bus_error(int node_id, struct mce *m)
{
	__amd64_decode_bus_error(mcis[node_id], m);
}