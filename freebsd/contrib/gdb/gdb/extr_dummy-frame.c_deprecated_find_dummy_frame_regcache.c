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
struct regcache {int dummy; } ;
struct dummy_frame {struct regcache* regcache; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct dummy_frame* find_dummy_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct regcache *
deprecated_find_dummy_frame_regcache (CORE_ADDR pc, CORE_ADDR fp)
{
  struct dummy_frame *dummy = find_dummy_frame (pc, fp);
  if (dummy != NULL)
    return dummy->regcache;
  else
    return NULL;
}