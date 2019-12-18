#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_7__ {int /*<<< orphan*/  bounds; } ;
struct TYPE_8__ {TYPE_1__ array; } ;
struct TYPE_9__ {TYPE_2__ u; struct TYPE_9__* declarator; } ;
typedef  TYPE_3__ cp_declarator ;

/* Variables and functions */
 int /*<<< orphan*/  cdk_array ; 
 TYPE_3__* make_declarator (int /*<<< orphan*/ ) ; 

cp_declarator *
make_array_declarator (cp_declarator *element, tree bounds)
{
  cp_declarator *declarator;

  declarator = make_declarator (cdk_array);
  declarator->declarator = element;
  declarator->u.array.bounds = bounds;

  return declarator;
}