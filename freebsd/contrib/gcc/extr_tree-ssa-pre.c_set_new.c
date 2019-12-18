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
typedef  TYPE_1__* value_set_t ;
struct TYPE_3__ {int indexed; int /*<<< orphan*/ * values; scalar_t__ length; int /*<<< orphan*/ * tail; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 scalar_t__ pool_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value_set_pool ; 

__attribute__((used)) static value_set_t
set_new  (bool indexed)
{
  value_set_t ret;
  ret = (value_set_t) pool_alloc (value_set_pool);
  ret->head = ret->tail = NULL;
  ret->length = 0;
  ret->indexed = indexed;
  ret->values = NULL;
  return ret;
}