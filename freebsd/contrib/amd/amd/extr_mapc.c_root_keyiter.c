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
typedef  int /*<<< orphan*/  opaque_t ;
typedef  int /*<<< orphan*/  key_fun ;

/* Variables and functions */
 int mapc_keyiter (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ root_map ; 

int
root_keyiter(key_fun *fn, opaque_t arg)
{
  if (root_map) {
    int c = mapc_keyiter(root_map, fn, arg);
    return c;
  }

  return 0;
}