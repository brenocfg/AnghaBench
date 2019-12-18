#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* fibnode_t ;
typedef  int fibheapkey_t ;
typedef  int /*<<< orphan*/  fibheap_t ;
struct TYPE_4__ {int key; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  fibheap_replace_key_data (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 

fibheapkey_t
fibheap_replace_key (fibheap_t heap, fibnode_t node, fibheapkey_t key)
{
  int okey = node->key;
  fibheap_replace_key_data (heap, node, key, node->data);
  return okey;
}