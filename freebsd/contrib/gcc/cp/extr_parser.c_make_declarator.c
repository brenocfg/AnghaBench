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
typedef  int /*<<< orphan*/  cp_declarator_kind ;
struct TYPE_3__ {int /*<<< orphan*/ * declarator; int /*<<< orphan*/  attributes; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ cp_declarator ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ alloc_declarator (int) ; 

__attribute__((used)) static cp_declarator *
make_declarator (cp_declarator_kind kind)
{
  cp_declarator *declarator;

  declarator = (cp_declarator *) alloc_declarator (sizeof (cp_declarator));
  declarator->kind = kind;
  declarator->attributes = NULL_TREE;
  declarator->declarator = NULL;

  return declarator;
}