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
struct TYPE_7__ {int mask; scalar_t__ p; int /*<<< orphan*/  slack; TYPE_1__** buckets; } ;
struct TYPE_6__ {int hash; struct TYPE_6__* link; } ;
typedef  scalar_t__ FT_UInt ;
typedef  TYPE_1__* FTC_Node ;
typedef  TYPE_2__* FTC_Cache ;

/* Variables and functions */
 int /*<<< orphan*/  FT_TRACE0 (char*) ; 
 int /*<<< orphan*/  ftc_cache_resize (TYPE_2__*) ; 

__attribute__((used)) static void
  ftc_node_hash_unlink( FTC_Node   node0,
                        FTC_Cache  cache )
  {
    FTC_Node  *pnode;
    FT_UInt    idx;


    idx = (FT_UInt)( node0->hash & cache->mask );
    if ( idx < cache->p )
      idx = (FT_UInt)( node0->hash & ( 2 * cache->mask + 1 ) );

    pnode = cache->buckets + idx;

    for (;;)
    {
      FTC_Node  node = *pnode;


      if ( node == NULL )
      {
        FT_TRACE0(( "ftc_node_hash_unlink: unknown node\n" ));
        return;
      }

      if ( node == node0 )
        break;

      pnode = &(*pnode)->link;
    }

    *pnode      = node0->link;
    node0->link = NULL;

    cache->slack++;
    ftc_cache_resize( cache );
  }