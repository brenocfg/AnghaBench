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
struct cgraph_node {int /*<<< orphan*/  decl; } ;

/* Variables and functions */
 scalar_t__ DECL_UNINLINABLE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ipcp_method_dont_insert_const (struct cgraph_node *mt)
{
  /* ??? Handle pending sizes case.  */
  if (DECL_UNINLINABLE (mt->decl))
    return true;
  return false;
}