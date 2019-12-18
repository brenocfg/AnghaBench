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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct frame_info* create_new_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 

struct frame_info *
alpha_setup_arbitrary_frame (int argc, CORE_ADDR *argv)
{
  if (argc != 2)
    error ("ALPHA frame specifications require two arguments: sp and pc");

  return create_new_frame (argv[0], argv[1]);
}