#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int (* lookup ) (int /*<<< orphan*/ *) ;int size; scalar_t__ (* compare ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;TYPE_1__** table; } ;
struct TYPE_5__ {int /*<<< orphan*/  key; } ;
typedef  int FT_ULong ;
typedef  TYPE_1__* FT_Hashnode ;
typedef  int /*<<< orphan*/  FT_Hashkey ;
typedef  TYPE_2__* FT_Hash ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static FT_Hashnode*
  hash_bucket( FT_Hashkey  key,
               FT_Hash     hash )
  {
    FT_ULong      res = 0;
    FT_Hashnode*  bp  = hash->table;
    FT_Hashnode*  ndp;


    res = (hash->lookup)( &key );

    ndp = bp + ( res % hash->size );
    while ( *ndp )
    {
      if ( (hash->compare)( &(*ndp)->key, &key ) )
        break;

      ndp--;
      if ( ndp < bp )
        ndp = bp + ( hash->size - 1 );
    }

    return ndp;
  }