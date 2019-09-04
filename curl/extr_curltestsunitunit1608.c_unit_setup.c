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
struct TYPE_2__ {struct TYPE_2__* ai_next; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int NUM_ADDRS ; 
 TYPE_1__* addrs ; 

__attribute__((used)) static CURLcode unit_setup(void)
{
  int i;
  for(i = 0; i < NUM_ADDRS - 1; i++) {
    addrs[i].ai_next = &addrs[i + 1];
  }

  return CURLE_OK;
}