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
typedef  int /*<<< orphan*/  unichar ;
struct TYPE_4__ {struct TYPE_4__* next; void* value; void* key; } ;
typedef  TYPE_1__ rc_ver_stringinfo ;

/* Variables and functions */
 scalar_t__ res_alloc (int) ; 
 void* unichar_dup (int /*<<< orphan*/  const*) ; 

rc_ver_stringinfo *
append_verval (rc_ver_stringinfo *strings, const unichar *key,
	       const unichar *value)
{
  rc_ver_stringinfo *vs, **pp;

  vs = (rc_ver_stringinfo *) res_alloc (sizeof (rc_ver_stringinfo));
  vs->next = NULL;
  vs->key = unichar_dup (key);
  vs->value = unichar_dup (value);

  for (pp = &strings; *pp != NULL; pp = &(*pp)->next)
    ;
  *pp = vs;

  return strings;
}