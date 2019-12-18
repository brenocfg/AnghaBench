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
 int /*<<< orphan*/  ht_dump_statistics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ident_hash ; 

void
stringpool_statistics (void)
{
  ht_dump_statistics (ident_hash);
}