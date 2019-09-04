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
struct curltime {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct Curl_tree {struct Curl_tree* larger; TYPE_1__* samep; int /*<<< orphan*/  smaller; int /*<<< orphan*/  key; struct Curl_tree* samen; } ;
struct TYPE_2__ {struct Curl_tree* samen; } ;

/* Variables and functions */
 struct Curl_tree* Curl_splay (struct curltime,struct Curl_tree*) ; 
 scalar_t__ compare (struct curltime,int /*<<< orphan*/ ) ; 

struct Curl_tree *Curl_splaygetbest(struct curltime i,
                                    struct Curl_tree *t,
                                    struct Curl_tree **removed)
{
  static struct curltime tv_zero = {0, 0};
  struct Curl_tree *x;

  if(!t) {
    *removed = NULL; /* none removed since there was no root */
    return NULL;
  }

  /* find smallest */
  t = Curl_splay(tv_zero, t);
  if(compare(i, t->key) < 0) {
    /* even the smallest is too big */
    *removed = NULL;
    return t;
  }

  /* FIRST! Check if there is a list with identical keys */
  x = t->samen;
  if(x != t) {
    /* there is, pick one from the list */

    /* 'x' is the new root node */

    x->key = t->key;
    x->larger = t->larger;
    x->smaller = t->smaller;
    x->samep = t->samep;
    t->samep->samen = x;

    *removed = t;
    return x; /* new root */
  }

  /* we splayed the tree to the smallest element, there is no smaller */
  x = t->larger;
  *removed = t;

  return x;
}