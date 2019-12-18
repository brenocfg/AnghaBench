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
 int /*<<< orphan*/  mdns_test_search_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  search ; 

__attribute__((used)) static void mdns_test_query_free(void)
{
    mdns_test_search_free(search);
}