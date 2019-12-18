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
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static const char *
type_from_format (int c)
{
  switch (c)
    {
    case 'i':
      return "int ";

    case 'w':
      return "HOST_WIDE_INT ";

    case 's':
      return "const char *";

    case 'e':  case 'u':
      return "rtx ";

    case 'E':
      return "rtvec ";
    case 'b':
      return "struct bitmap_head_def *";  /* bitmap - typedef not available */
    case 't':
      return "union tree_node *";  /* tree - typedef not available */
    case 'B':
      return "struct basic_block_def *";  /* basic block - typedef not available */
    default:
      gcc_unreachable ();
    }
}