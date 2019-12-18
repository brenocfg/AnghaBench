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
struct dom_info {size_t* set_chain; size_t* path_min; scalar_t__* key; } ;
typedef  size_t TBB ;

/* Variables and functions */
 int /*<<< orphan*/  compress (struct dom_info*,size_t) ; 

__attribute__((used)) static inline TBB
eval (struct dom_info *di, TBB v)
{
  /* The representant of the set V is in, also called root (as the set
     representation is a tree).  */
  TBB rep = di->set_chain[v];

  /* V itself is the root.  */
  if (!rep)
    return di->path_min[v];

  /* Compress only if necessary.  */
  if (di->set_chain[rep])
    {
      compress (di, v);
      rep = di->set_chain[v];
    }

  if (di->key[di->path_min[rep]] >= di->key[di->path_min[v]])
    return di->path_min[v];
  else
    return di->path_min[rep];
}