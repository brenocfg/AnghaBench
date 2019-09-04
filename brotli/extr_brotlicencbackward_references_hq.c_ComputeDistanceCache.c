#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t shortcut; } ;
struct TYPE_7__ {int dcode_insert_length; TYPE_1__ u; } ;
typedef  TYPE_2__ ZopfliNode ;

/* Variables and functions */
 size_t ZopfliNodeCopyDistance (TYPE_2__ const*) ; 
 size_t ZopfliNodeCopyLength (TYPE_2__ const*) ; 

__attribute__((used)) static void ComputeDistanceCache(const size_t pos,
                                 const int* starting_dist_cache,
                                 const ZopfliNode* nodes,
                                 int* dist_cache) {
  int idx = 0;
  size_t p = nodes[pos].u.shortcut;
  while (idx < 4 && p > 0) {
    const size_t ilen = nodes[p].dcode_insert_length & 0x7FFFFFF;
    const size_t clen = ZopfliNodeCopyLength(&nodes[p]);
    const size_t dist = ZopfliNodeCopyDistance(&nodes[p]);
    dist_cache[idx++] = (int)dist;
    /* Because of prerequisite, p >= clen + ilen >= 2. */
    p = nodes[p - clen - ilen].u.shortcut;
  }
  for (; idx < 4; ++idx) {
    dist_cache[idx] = *starting_dist_cache++;
  }
}