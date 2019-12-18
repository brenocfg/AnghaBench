#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct htab {int dummy; } ;
typedef  TYPE_1__* htab_t ;
typedef  int /*<<< orphan*/  htab_hash ;
typedef  int /*<<< orphan*/  (* htab_free ) (TYPE_1__*) ;
typedef  int /*<<< orphan*/  htab_eq ;
typedef  int /*<<< orphan*/  htab_del ;
typedef  scalar_t__ (* htab_alloc ) (size_t,int) ;
struct TYPE_8__ {size_t prime; } ;
struct TYPE_7__ {size_t size; unsigned int size_prime_index; int /*<<< orphan*/  (* free_f ) (TYPE_1__*) ;scalar_t__ (* alloc_f ) (size_t,int) ;int /*<<< orphan*/  del_f; int /*<<< orphan*/  eq_f; int /*<<< orphan*/  hash_f; int /*<<< orphan*/ * entries; } ;
typedef  int /*<<< orphan*/  PTR ;

/* Variables and functions */
 unsigned int higher_prime_index (size_t) ; 
 TYPE_4__* prime_tab ; 
 scalar_t__ stub1 (size_t,int) ; 
 scalar_t__ stub2 (size_t,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*) ; 

htab_t
htab_create_alloc (size_t size, htab_hash hash_f, htab_eq eq_f,
                   htab_del del_f, htab_alloc alloc_f, htab_free free_f)
{
  htab_t result;
  unsigned int size_prime_index;

  size_prime_index = higher_prime_index (size);
  size = prime_tab[size_prime_index].prime;

  result = (htab_t) (*alloc_f) (1, sizeof (struct htab));
  if (result == NULL)
    return NULL;
  result->entries = (PTR *) (*alloc_f) (size, sizeof (PTR));
  if (result->entries == NULL)
    {
      if (free_f != NULL)
	(*free_f) (result);
      return NULL;
    }
  result->size = size;
  result->size_prime_index = size_prime_index;
  result->hash_f = hash_f;
  result->eq_f = eq_f;
  result->del_f = del_f;
  result->alloc_f = alloc_f;
  result->free_f = free_f;
  return result;
}