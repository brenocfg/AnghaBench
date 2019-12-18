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
struct constant_descriptor_tree {int /*<<< orphan*/  hash; } ;
typedef  int /*<<< orphan*/  hashval_t ;

/* Variables and functions */

__attribute__((used)) static hashval_t
const_desc_hash (const void *ptr)
{
  return ((struct constant_descriptor_tree *)ptr)->hash;
}