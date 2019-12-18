#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* tree ;
typedef  scalar_t__ function_ann_t ;
struct TYPE_10__ {TYPE_2__* ann; } ;
struct TYPE_11__ {TYPE_3__ common; } ;
struct TYPE_8__ {scalar_t__ type; } ;
struct TYPE_9__ {TYPE_1__ common; } ;

/* Variables and functions */
 scalar_t__ FUNCTION_ANN ; 
 scalar_t__ create_function_ann (TYPE_4__*) ; 
 scalar_t__ function_ann (TYPE_4__*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static inline function_ann_t
get_function_ann (tree var)
{
  function_ann_t ann = function_ann (var);
  gcc_assert (!var->common.ann || var->common.ann->common.type == FUNCTION_ANN);
  return (ann) ? ann : create_function_ann (var);
}