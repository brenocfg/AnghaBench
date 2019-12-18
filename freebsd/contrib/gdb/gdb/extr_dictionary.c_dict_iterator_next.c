#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct symbol {int dummy; } ;
struct dict_iterator {int dummy; } ;
struct TYPE_2__ {struct symbol* (* iterator_next ) (struct dict_iterator*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DICT_ITERATOR_DICT (struct dict_iterator*) ; 
 TYPE_1__* DICT_VECTOR (int /*<<< orphan*/ ) ; 
 struct symbol* stub1 (struct dict_iterator*) ; 

struct symbol *
dict_iterator_next (struct dict_iterator *iterator)
{
  return (DICT_VECTOR (DICT_ITERATOR_DICT (iterator)))
    ->iterator_next (iterator);
}