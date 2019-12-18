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
struct frame_info {int dummy; } ;
struct amd64_frame_cache {int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct amd64_frame_cache* amd64_frame_cache (struct frame_info*,void**) ; 

__attribute__((used)) static CORE_ADDR
amd64_frame_base_address (struct frame_info *next_frame, void **this_cache)
{
  struct amd64_frame_cache *cache =
    amd64_frame_cache (next_frame, this_cache);

  return cache->base;
}