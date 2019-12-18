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
struct fibnode {void* data; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  fibnode_t ;
typedef  int /*<<< orphan*/  fibheapkey_t ;
typedef  int /*<<< orphan*/  fibheap_t ;

/* Variables and functions */
 int fibheap_compare (int /*<<< orphan*/ ,struct fibnode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
fibheap_comp_data (fibheap_t heap, fibheapkey_t key, void *data, fibnode_t b)
{
  struct fibnode a;

  a.key = key;
  a.data = data;

  return fibheap_compare (heap, &a, b);
}