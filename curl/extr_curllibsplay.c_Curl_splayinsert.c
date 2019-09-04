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
typedef  int /*<<< orphan*/  time_t ;
struct curltime {unsigned int member_1; int /*<<< orphan*/  member_0; } ;
struct Curl_tree {struct Curl_tree* samep; struct Curl_tree* samen; struct curltime key; struct Curl_tree* larger; struct Curl_tree* smaller; } ;

/* Variables and functions */
 struct Curl_tree* Curl_splay (struct curltime,struct Curl_tree*) ; 
 scalar_t__ compare (struct curltime,struct curltime) ; 

struct Curl_tree *Curl_splayinsert(struct curltime i,
                                   struct Curl_tree *t,
                                   struct Curl_tree *node)
{
  static const struct curltime KEY_NOTUSED = {
    (time_t)-1, (unsigned int)-1
  }; /* will *NEVER* appear */

  if(node == NULL)
    return t;

  if(t != NULL) {
    t = Curl_splay(i, t);
    if(compare(i, t->key) == 0) {
      /* There already exists a node in the tree with the very same key. Build
         a doubly-linked circular list of nodes. We add the new 'node' struct
         to the end of this list. */

      node->key = KEY_NOTUSED; /* we set the key in the sub node to NOTUSED
                                  to quickly identify this node as a subnode */
      node->samen = t;
      node->samep = t->samep;
      t->samep->samen = node;
      t->samep = node;

      return t; /* the root node always stays the same */
    }
  }

  if(t == NULL) {
    node->smaller = node->larger = NULL;
  }
  else if(compare(i, t->key) < 0) {
    node->smaller = t->smaller;
    node->larger = t;
    t->smaller = NULL;

  }
  else {
    node->larger = t->larger;
    node->smaller = t;
    t->larger = NULL;
  }
  node->key = i;

  /* no identical nodes (yet), we are the only one in the list of nodes */
  node->samen = node;
  node->samep = node;
  return node;
}