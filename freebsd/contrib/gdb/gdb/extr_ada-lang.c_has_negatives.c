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
struct type {int dummy; } ;

/* Variables and functions */
 int TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_INT 129 
#define  TYPE_CODE_RANGE 128 
 int /*<<< orphan*/  TYPE_LOW_BOUND (struct type*) ; 
 int /*<<< orphan*/  TYPE_UNSIGNED (struct type*) ; 

__attribute__((used)) static int
has_negatives (struct type *type)
{
  switch (TYPE_CODE (type))
    {
    default:
      return 0;
    case TYPE_CODE_INT:
      return !TYPE_UNSIGNED (type);
    case TYPE_CODE_RANGE:
      return TYPE_LOW_BOUND (type) < 0;
    }
}