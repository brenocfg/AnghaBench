#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* varray_type ;
struct TYPE_7__ {size_t size; } ;
struct TYPE_5__ {int /*<<< orphan*/  vdt_c; } ;
struct TYPE_6__ {size_t type; size_t num_elements; scalar_t__ elements_used; TYPE_1__ data; } ;

/* Variables and functions */
 TYPE_4__* element ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

void
varray_clear (varray_type va)
{
  size_t data_size = element[va->type].size * va->num_elements;

  memset (va->data.vdt_c, 0, data_size);
  va->elements_used = 0;
}