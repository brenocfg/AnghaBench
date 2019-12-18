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
struct loop {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  empty_block_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_end_pos (struct loop*) ; 
 int /*<<< orphan*/  ip_normal_pos (struct loop*) ; 

__attribute__((used)) static bool
allow_ip_end_pos_p (struct loop *loop)
{
  if (!ip_normal_pos (loop))
    return true;

  if (!empty_block_p (ip_end_pos (loop)))
    return true;

  return false;
}