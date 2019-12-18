#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* de_next; } ;
typedef  TYPE_1__ dict_ent ;
struct TYPE_9__ {TYPE_1__** de; } ;
typedef  TYPE_2__ dict ;

/* Variables and functions */
 int /*<<< orphan*/  dict_add_data (TYPE_1__*,char*) ; 
 size_t dict_hash (char*) ; 
 TYPE_1__* dict_locate (TYPE_2__*,char*) ; 
 TYPE_1__* new_dict_ent (char*) ; 

void
dict_add(dict *dp, char *k, char *v)
{
  dict_ent *de = dict_locate(dp, k);

  if (!de) {
    dict_ent **dep = &dp->de[dict_hash(k)];
    de = new_dict_ent(k);
    de->de_next = *dep;
    *dep = de;
  }
  dict_add_data(de, v);
}