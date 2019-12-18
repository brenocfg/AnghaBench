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
struct type_brand_s {int seq; int /*<<< orphan*/  name; } ;
typedef  scalar_t__ splay_tree_key ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int 
compare_type_brand (splay_tree_key sk1, splay_tree_key sk2)
{
  struct type_brand_s * k1 = (struct type_brand_s *) sk1;
  struct type_brand_s * k2 = (struct type_brand_s *) sk2;

  int value = strcmp(k1->name, k2->name);
  if (value == 0)
    return k2->seq - k1->seq;
  else 
    return value;
}