#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* fibnode_t ;
struct TYPE_3__ {struct TYPE_3__* right; struct TYPE_3__* left; } ;

/* Variables and functions */
 scalar_t__ xcalloc (int,int) ; 

__attribute__((used)) static fibnode_t
fibnode_new (void)
{
  fibnode_t node;

  node = (fibnode_t) xcalloc (1, sizeof *node);
  node->left = node;
  node->right = node;

  return node;
}