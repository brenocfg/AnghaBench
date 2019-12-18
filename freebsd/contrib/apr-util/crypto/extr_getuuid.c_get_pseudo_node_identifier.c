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

/* Variables and functions */
 int /*<<< orphan*/  get_random_info (unsigned char*) ; 

__attribute__((used)) static void get_pseudo_node_identifier(unsigned char *node)
{
    get_random_info(node);
    node[0] |= 0x01;                    /* this designates a random multicast node ID */
}