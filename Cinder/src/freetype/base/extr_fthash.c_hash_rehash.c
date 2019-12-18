#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ size; int limit; TYPE_1__** table; } ;
struct TYPE_8__ {int /*<<< orphan*/  key; } ;
typedef  scalar_t__ FT_UInt ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  TYPE_1__* FT_Hashnode ;
typedef  TYPE_2__* FT_Hash ;
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Err_Ok ; 
 int /*<<< orphan*/  FT_FREE (TYPE_1__**) ; 
 scalar_t__ FT_NEW_ARRAY (TYPE_1__**,int) ; 
 TYPE_1__** hash_bucket (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static FT_Error
  hash_rehash( FT_Hash    hash,
               FT_Memory  memory )
  {
    FT_Hashnode*  obp = hash->table;
    FT_Hashnode*  bp;
    FT_Hashnode*  nbp;

    FT_UInt   i, sz = hash->size;
    FT_Error  error = FT_Err_Ok;


    hash->size <<= 1;
    hash->limit  = hash->size / 3;

    if ( FT_NEW_ARRAY( hash->table, hash->size ) )
      goto Exit;

    for ( i = 0, bp = obp; i < sz; i++, bp++ )
    {
      if ( *bp )
      {
        nbp = hash_bucket( (*bp)->key, hash );
        *nbp = *bp;
      }
    }

    FT_FREE( obp );

  Exit:
    return error;
  }