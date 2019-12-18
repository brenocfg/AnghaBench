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
struct dictionary {int dummy; } ;
struct dict_iterator {int dummy; } ;
struct TYPE_2__ {struct symbol* (* iter_name_first ) (struct dictionary const*,char const*,struct dict_iterator*) ;} ;

/* Variables and functions */
 TYPE_1__* DICT_VECTOR (struct dictionary const*) ; 
 struct symbol* stub1 (struct dictionary const*,char const*,struct dict_iterator*) ; 

struct symbol *
dict_iter_name_first (const struct dictionary *dict,
		      const char *name,
		      struct dict_iterator *iterator)
{
  return (DICT_VECTOR (dict))->iter_name_first (dict, name, iterator);
}