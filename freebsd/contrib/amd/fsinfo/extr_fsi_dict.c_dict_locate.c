#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* de_next; int /*<<< orphan*/  de_key; } ;
typedef  TYPE_1__ dict_ent ;
struct TYPE_6__ {TYPE_1__** de; } ;
typedef  TYPE_2__ dict ;

/* Variables and functions */
 int /*<<< orphan*/  STREQ (int /*<<< orphan*/ ,char*) ; 
 size_t dict_hash (char*) ; 

dict_ent *
dict_locate(dict *dp, char *k)
{
  dict_ent *de = dp->de[dict_hash(k)];

  while (de && !STREQ(de->de_key, k))
    de = de->de_next;
  return de;
}