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
struct curl_hash_element {scalar_t__ key_len; int /*<<< orphan*/ * ptr; } ;
struct curl_hash {int /*<<< orphan*/  (* dtor ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct curl_hash_element*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hash_element_dtor(void *user, void *element)
{
  struct curl_hash *h = (struct curl_hash *) user;
  struct curl_hash_element *e = (struct curl_hash_element *) element;

  if(e->ptr) {
    h->dtor(e->ptr);
    e->ptr = NULL;
  }

  e->key_len = 0;

  free(e);
}