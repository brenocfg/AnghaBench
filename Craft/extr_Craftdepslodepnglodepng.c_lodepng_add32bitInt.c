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
struct TYPE_4__ {int size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ ucvector ;

/* Variables and functions */
 int /*<<< orphan*/  lodepng_set32bitInt (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  ucvector_resize (TYPE_1__*,int) ; 

__attribute__((used)) static void lodepng_add32bitInt(ucvector* buffer, unsigned value)
{
  ucvector_resize(buffer, buffer->size + 4); /*todo: give error if resize failed*/
  lodepng_set32bitInt(&buffer->data[buffer->size - 4], value);
}