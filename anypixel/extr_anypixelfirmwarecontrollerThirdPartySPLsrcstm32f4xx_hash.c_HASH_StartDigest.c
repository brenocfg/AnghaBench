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
struct TYPE_2__ {int /*<<< orphan*/  STR; } ;

/* Variables and functions */
 TYPE_1__* HASH ; 
 int /*<<< orphan*/  HASH_STR_DCAL ; 

void HASH_StartDigest(void)
{
  /* Start the Digest calculation */
  HASH->STR |= HASH_STR_DCAL;
}