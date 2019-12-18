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
struct curltime {int dummy; } ;
struct Curl_tree {struct Curl_tree* smaller; struct Curl_tree* larger; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 long compare (struct curltime,int /*<<< orphan*/ ) ; 

struct Curl_tree *Curl_splay(struct curltime i,
                             struct Curl_tree *t)
{
  struct Curl_tree N, *l, *r, *y;

  if(t == NULL)
    return t;
  N.smaller = N.larger = NULL;
  l = r = &N;

  for(;;) {
    long comp = compare(i, t->key);
    if(comp < 0) {
      if(t->smaller == NULL)
        break;
      if(compare(i, t->smaller->key) < 0) {
        y = t->smaller;                           /* rotate smaller */
        t->smaller = y->larger;
        y->larger = t;
        t = y;
        if(t->smaller == NULL)
          break;
      }
      r->smaller = t;                               /* link smaller */
      r = t;
      t = t->smaller;
    }
    else if(comp > 0) {
      if(t->larger == NULL)
        break;
      if(compare(i, t->larger->key) > 0) {
        y = t->larger;                          /* rotate larger */
        t->larger = y->smaller;
        y->smaller = t;
        t = y;
        if(t->larger == NULL)
          break;
      }
      l->larger = t;                              /* link larger */
      l = t;
      t = t->larger;
    }
    else
      break;
  }

  l->larger = t->smaller;                                /* assemble */
  r->smaller = t->larger;
  t->smaller = N.larger;
  t->larger = N.smaller;

  return t;
}