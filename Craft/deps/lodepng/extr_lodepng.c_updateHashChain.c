#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* val; int* head; int* chain; } ;
typedef  TYPE_1__ Hash ;

/* Variables and functions */

__attribute__((used)) static void updateHashChain(Hash* hash, size_t pos, int hashval, unsigned windowsize)
{
  unsigned wpos = pos % windowsize;
  hash->val[wpos] = hashval;
  if(hash->head[hashval] != -1) hash->chain[wpos] = hash->head[hashval];
  hash->head[hashval] = wpos;
}