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
typedef  int /*<<< orphan*/  time_t ;
struct curltime {unsigned int member_1; int /*<<< orphan*/  member_0; } ;
struct Curl_tree {struct Curl_tree* larger; struct Curl_tree* smaller; int /*<<< orphan*/  key; TYPE_1__* samep; struct Curl_tree* samen; } ;
struct TYPE_2__ {struct Curl_tree* samen; } ;

/* Variables and functions */
 struct Curl_tree* Curl_splay (int /*<<< orphan*/ ,struct Curl_tree*) ; 
 scalar_t__ compare (struct curltime const,int /*<<< orphan*/ ) ; 

int Curl_splayremovebyaddr(struct Curl_tree *t,
                           struct Curl_tree *removenode,
                           struct Curl_tree **newroot)
{
  static const struct curltime KEY_NOTUSED = {
    (time_t)-1, (unsigned int)-1
  }; /* will *NEVER* appear */
  struct Curl_tree *x;

  if(!t || !removenode)
    return 1;

  if(compare(KEY_NOTUSED, removenode->key) == 0) {
    /* Key set to NOTUSED means it is a subnode within a 'same' linked list
       and thus we can unlink it easily. */
    if(removenode->samen == removenode)
      /* A non-subnode should never be set to KEY_NOTUSED */
      return 3;

    removenode->samep->samen = removenode->samen;
    removenode->samen->samep = removenode->samep;

    /* Ensures that double-remove gets caught. */
    removenode->samen = removenode;

    *newroot = t; /* return the same root */
    return 0;
  }

  t = Curl_splay(removenode->key, t);

  /* First make sure that we got the same root node as the one we want
     to remove, as otherwise we might be trying to remove a node that
     isn't actually in the tree.

     We cannot just compare the keys here as a double remove in quick
     succession of a node with key != KEY_NOTUSED && same != NULL
     could return the same key but a different node. */
  if(t != removenode)
    return 2;

  /* Check if there is a list with identical sizes, as then we're trying to
     remove the root node of a list of nodes with identical keys. */
  x = t->samen;
  if(x != t) {
    /* 'x' is the new root node, we just make it use the root node's
       smaller/larger links */

    x->key = t->key;
    x->larger = t->larger;
    x->smaller = t->smaller;
    x->samep = t->samep;
    t->samep->samen = x;
  }
  else {
    /* Remove the root node */
    if(t->smaller == NULL)
      x = t->larger;
    else {
      x = Curl_splay(removenode->key, t->smaller);
      x->larger = t->larger;
    }
  }

  *newroot = x; /* store new root pointer */

  return 0;
}